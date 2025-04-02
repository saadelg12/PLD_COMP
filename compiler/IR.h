#pragma once

#include "generated/ifccBaseVisitor.h"
#include "SymbolTableVisitor.h"
#include "Type.h"
#include <map>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

// ---------- PRÉDECLARATIONS ----------
class IRInstr;
class BasicBlock;
class CFG;

// ---------- INSTRUCTION IR ----------
class IRInstr
{
public:
	enum Operation
	{
		ldconst,
		copy,
		add,
		sub,
		mul,
		div,
		mod,
		cmp_eq,
		cmp_lt,
		cmp_le,
		cmp_ge,
		bitwise_and,
		bitwise_or,
		bitwise_xor,
		ret
	};

	IRInstr(BasicBlock *bb_, Operation op, Type t, vector<string> params)
		: bb(bb_), op(op), t(t), params(params) {}

	Operation getOperation() const { return op; }

	void gen_asm(ostream &o);

	void gen_asm_arm(std::ostream &o);

private:
	BasicBlock *bb;
	Operation op;
	Type t;
	vector<string> params;

	string suffix_for_type(Type t)
	{
		switch (t)
		{
		case INT:
			return "l"; // long = 4 octets
		case CHAR:
			return "b"; // byte = 1 octet
		default:
			return "l"; // fallback = int
		}
	}
};

// ---------- BLOC DE BASE ----------
class BasicBlock
{
public:
	BasicBlock(CFG *cfg, string entry_label);
	void add_IRInstr(IRInstr::Operation op, Type t, vector<string> params);
	void gen_asm(ostream &o);

	string label;
	CFG *cfg;
	vector<IRInstr *> instrs;
	BasicBlock *exit_true = nullptr;
	BasicBlock *exit_false = nullptr;
};

// ---------- GRAPHE DE CONTRÔLE ----------
class CFG
{
public:
	CFG(void *ast_, const SymbolTableVisitor &symtab)
		: ast(ast_),
		  symbolTable(symtab.getSymbolTables()),
		  nextFreeSymbolIndex(symtab.getStackOffset()),
		  currentST_index(0),
		  last_ST_index(0) {}

	void add_bb(BasicBlock *bb) { bbs.push_back(bb); }

	void gen_asm(ostream &o);
	void gen_asm_prologue(ostream &o);
	void gen_asm_epilogue(ostream &o);

	string IR_reg_to_asm(const string &reg) const
	{
		int offset = get_var_index(reg);
		if (is_arm)
			return "[sp, #" + to_string(offset + 16) + "]"; // stack offset + frame alloc
		else
			return to_string(offset) + "(%rbp)";
	}

	int get_var_index(const string &name) const
	{
		SymbolTable *current_symbol_table = symbolTable.at(currentST_index);
		int res = current_symbol_table->get(name).symbolOffset;

		return res;
	}
	Type get_var_type(const string &name) const
	{
		SymbolTable *current_symbol_table = symbolTable.at(currentST_index);
		return current_symbol_table->get(name).symbolType;
	}

	string create_new_tempvar(Type t)
	{
		string name = "!tmp" + to_string(-nextFreeSymbolIndex);
		Symbol s;
		s.symbolName = name;
		s.symbolOffset = nextFreeSymbolIndex;
		s.symbolType = t;
		symbolTable.at(currentST_index)->table[name] = s;
		nextFreeSymbolIndex -= 4;
		return name;
	}

	int currentST_index;
	int last_ST_index;
	vector<BasicBlock *> bbs;
	vector<SymbolTable *> symbolTable;
	BasicBlock *current_bb;

	bool is_arm = false;	  // false = x86, true = ARM
	int stack_allocation = 0; // Allocation pour décalage de sp

private:
	void *ast;

	int nextFreeSymbolIndex;
};

// ---------- ASSEMBLEUR POUR IRInstr ----------
void IRInstr::gen_asm(ostream &o)
{

	string s = suffix_for_type(t); // suffix for instruction based on type
	string dst;

	if (op != ret)
	{
		dst = bb->cfg->IR_reg_to_asm(params[0]);
	}

	switch (op)
	{
	case ldconst:
		o << "    mov" << s << " $" << params[1] << ", " << dst << "\n";
		break;

	case copy:
		o << "    mov" << s << " " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
		o << "    mov" << s << " %eax, " << dst << "\n";
		break;

	case add:
		o << "    mov" << s << " " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
		o << "    add" << s << " " << bb->cfg->IR_reg_to_asm(params[2]) << ", %eax\n";
		o << "    mov" << s << " %eax, " << dst << "\n";
		break;

	case sub:
		o << "    mov" << s << " " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
		o << "    sub" << s << " " << bb->cfg->IR_reg_to_asm(params[2]) << ", %eax\n";
		o << "    mov" << s << " %eax, " << dst << "\n";
		break;

	case mul:
		o << "    mov" << s << " " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
		o << "    imul" << s << " " << bb->cfg->IR_reg_to_asm(params[2]) << ", %eax\n";
		o << "    mov" << s << " %eax, " << dst << "\n";
		break;

	case div:
		o << "    mov" << s << " " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
		o << "    cltd\n";
		o << "    idiv" << s << " " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    mov" << s << " %eax, " << dst << "\n";
		break;

	case mod:
		o << "    mov" << s << " " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
		o << "    cltd\n";
		o << "    idiv" << s << " " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    mov" << s << " %edx, " << dst << "\n";
		break;

	case cmp_eq:
		if (t == CHAR)
		{
			o << "    movb " << bb->cfg->IR_reg_to_asm(params[1]) << ", %al\n";
			o << "    cmpb " << bb->cfg->IR_reg_to_asm(params[2]) << ", %al\n";
		}
		else
		{
			o << "    movl " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
			o << "    cmpl " << bb->cfg->IR_reg_to_asm(params[2]) << ", %eax\n";
		}
		o << "    sete %al\n";
		o << "    movzbl %al, %eax\n";
		o << "    movl %eax, " << dst << "\n";
		break;

	case cmp_lt:
		if (t == CHAR)
		{
			o << "    movb " << bb->cfg->IR_reg_to_asm(params[1]) << ", %al\n";
			o << "    cmpb " << bb->cfg->IR_reg_to_asm(params[2]) << ", %al\n";
		}
		else
		{
			o << "    movl " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
			o << "    cmpl " << bb->cfg->IR_reg_to_asm(params[2]) << ", %eax\n";
		}
		o << "    setl %al\n";
		o << "    movzbl %al, %eax\n";
		o << "    movl %eax, " << dst << "\n";
		break;

	case cmp_le:
		if (t == CHAR)
		{
			o << "    movb " << bb->cfg->IR_reg_to_asm(params[1]) << ", %al\n";
			o << "    cmpb " << bb->cfg->IR_reg_to_asm(params[2]) << ", %al\n";
		}
		else
		{
			o << "    movl " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
			o << "    cmpl " << bb->cfg->IR_reg_to_asm(params[2]) << ", %eax\n";
		}
		o << "    setle %al\n";
		o << "    movzbl %al, %eax\n";
		o << "    movl %eax, " << dst << "\n";
		break;

	case cmp_ge:
		if (t == CHAR)
		{
			o << "    movb " << bb->cfg->IR_reg_to_asm(params[1]) << ", %al\n";
			o << "    cmpb " << bb->cfg->IR_reg_to_asm(params[2]) << ", %al\n";
		}
		else
		{
			o << "    movl " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
			o << "    cmpl " << bb->cfg->IR_reg_to_asm(params[2]) << ", %eax\n";
		}
		o << "    setge %al\n";
		o << "    movzbl %al, %eax\n";
		o << "    movl %eax, " << dst << "\n";
		break;

	case bitwise_and:
		o << "    mov" << s << " " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
		o << "    and" << s << " " << bb->cfg->IR_reg_to_asm(params[2]) << ", %eax\n";
		o << "    mov" << s << " %eax, " << dst << "\n";
		break;

	case bitwise_or:
		o << "    mov" << s << " " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
		o << "    or" << s << " " << bb->cfg->IR_reg_to_asm(params[2]) << ", %eax\n";
		o << "    mov" << s << " %eax, " << dst << "\n";
		break;

	case bitwise_xor:
		o << "    mov" << s << " " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
		o << "    xor" << s << " " << bb->cfg->IR_reg_to_asm(params[2]) << ", %eax\n";
		o << "    mov" << s << " %eax, " << dst << "\n";
		break;

	case ret:
	{
		const string &src = params[0];
		if (!src.empty() && src[0] == '$')
		{
			o << "    movl " << src << ", %eax\n";
		}
		else
		{
			o << "    mov" << s << " " << bb->cfg->IR_reg_to_asm(src) << ", %eax\n";
			if (s == "b")
			{
				o << "    movzbl %al, %eax\n"; // étend 8 bits → 32 bits
			}
		}
		o << "    leave\n";
		o << "    ret\n";
		break;
	}

	default:
		break;
	}
}

void IRInstr::gen_asm_arm(std::ostream &o)
{
	string dst = bb->cfg->IR_reg_to_asm(params[0]);
	string reg1 = "w1";
	string reg2 = "w2";
	string dst_reg = "w0";

	bool is_last_instr = (bb->instrs.back() == this);
	bool is_last_bb = (bb->cfg->bbs.back() == bb);
	bool skip_store = is_last_instr && is_last_bb && bb->cfg->current_bb == bb;

	switch (op)
	{
	case ldconst:
		o << "    mov " << dst_reg << ", #" << params[1] << "\n";
		if (!skip_store)
			o << "    str " << dst_reg << ", " << dst << "\n";
		break;

	case copy:
		o << "    ldr " << dst_reg << ", " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		if (!skip_store)
			o << "    str " << dst_reg << ", " << dst << "\n";
		break;

	case add:
	case sub:
	case mul:
	{
		string op_instr = (op == add) ? "add" : (op == sub) ? "sub"
															: "mul";
		o << "    ldr " << reg1 << ", " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr " << reg2 << ", " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    " << op_instr << " " << dst_reg << ", " << reg1 << ", " << reg2 << "\n";

		// 💡 NE FAIS PAS DE STR si l’instruction suivante est un ret de la même variable
		bool next_is_ret = false;
		if (bb->instrs.size() >= 2)
		{
			IRInstr *next = bb->instrs[bb->instrs.size() - 1];
			if (next->getOperation() == ret && next->params[0] == params[0])
			{
				next_is_ret = true;
			}
		}

		if (!next_is_ret)
			o << "    str " << dst_reg << ", " << dst << "\n";

		break;
	}

	case div:
	{
		o << "    ldr " << reg1 << ", " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr " << reg2 << ", " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    sdiv " << dst_reg << ", " << reg1 << ", " << reg2 << "\n";
		o << "    str " << dst_reg << ", " << dst << "\n";
		break;
	}

	case mod:
	{
		o << "    ldr " << reg1 << ", " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr " << reg2 << ", " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    sdiv w3, " << reg1 << ", " << reg2 << "\n";
		o << "    msub " << dst_reg << ", w3, " << reg2 << ", " << reg1 << " // w0 = lhs - (lhs / rhs) * rhs\n";
		o << "    str " << dst_reg << ", " << dst << "\n";
		break;
	}

	case cmp_eq:
	{
		o << "    ldr " << reg1 << ", " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr " << reg2 << ", " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    cmp " << reg1 << ", " << reg2 << "\n";
		o << "    cset " << dst_reg << ", eq\n";
		o << "    str " << dst_reg << ", " << dst << "\n";
		break;
	}

	case cmp_lt:
	{
		o << "    ldr " << reg1 << ", " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr " << reg2 << ", " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    cmp " << reg1 << ", " << reg2 << "\n";
		o << "    cset " << dst_reg << ", lt\n";
		o << "    str " << dst_reg << ", " << dst << "\n";
		break;
	}

	case cmp_le:
	{
		o << "    ldr " << reg1 << ", " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr " << reg2 << ", " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    cmp " << reg1 << ", " << reg2 << "\n";
		o << "    cset " << dst_reg << ", le\n";
		o << "    str " << dst_reg << ", " << dst << "\n";
		break;
	}

	case cmp_ge:
	{
		o << "    ldr " << reg1 << ", " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr " << reg2 << ", " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    cmp " << reg1 << ", " << reg2 << "\n";
		o << "    cset " << dst_reg << ", ge\n";
		o << "    str " << dst_reg << ", " << dst << "\n";
		break;
	}

	case bitwise_and:
	{
		o << "    ldr " << reg1 << ", " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr " << reg2 << ", " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    and " << dst_reg << ", " << reg1 << ", " << reg2 << "\n";
		o << "    str " << dst_reg << ", " << dst << "\n";
		break;
	}

	case bitwise_or:
	{
		o << "    ldr " << reg1 << ", " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr " << reg2 << ", " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    orr " << dst_reg << ", " << reg1 << ", " << reg2 << "\n";
		o << "    str " << dst_reg << ", " << dst << "\n";
		break;
	}

	case bitwise_xor:
	{
		o << "    ldr " << reg1 << ", " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr " << reg2 << ", " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    eor " << dst_reg << ", " << reg1 << ", " << reg2 << "\n";
		o << "    str " << dst_reg << ", " << dst << "\n";
		break;
	}

	case ret:
		if (!params[0].empty() && params[0][0] == '$')
		{
			o << "    mov w0, #" << params[0].substr(1) << "\n";
		}
		else
		{
			// vérifier si la valeur a été produite dans w0
			bool already_in_w0 = false;
			if (!bb->instrs.empty() && bb->instrs.back() == this && bb->instrs.size() >= 2)
			{
				IRInstr *prev = bb->instrs[bb->instrs.size() - 2];
				if ((prev->getOperation() == add || prev->getOperation() == sub || prev->getOperation() == mul) &&
					prev->params[0] == params[0])
				{
					already_in_w0 = true;
				}
			}

			if (!already_in_w0)
				o << "    ldr w0, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		}
		o << "    add sp, sp, #" << bb->cfg->stack_allocation << "\n";
		o << "    ret\n";
		break;

	default:
		o << "    // [ARM64] Instruction non supportée pour " << op << "\n";
		break;
	}
}

// ---------- ASSEMBLEUR POUR BasicBlock ----------
BasicBlock::BasicBlock(CFG *cfg_, string entry_label)
	: cfg(cfg_), label(entry_label) {}

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params)
{
	instrs.push_back(new IRInstr(this, op, t, params));
}

void BasicBlock::gen_asm(ostream &o)
{
	for (auto instr : instrs)
	{
		if (cfg->is_arm)
			instr->gen_asm_arm(o);
		else
			instr->gen_asm(o);
	}
}

// ---------- ASSEMBLEUR POUR CFG ----------
void CFG::gen_asm_prologue(ostream &o)
{
	o << "    pushq %rbp\n";
	o << "    movq %rsp, %rbp\n";

	int total = -nextFreeSymbolIndex;
	if (total % 16 != 0)
		total += (16 - (total % 16));
	o << "    subq $" << total << ", %rsp\n";
}

void CFG::gen_asm_epilogue(ostream &o)
{
	o << "    leave\n";
	o << "    ret\n";
}

void CFG::gen_asm(std::ostream &o)
{
	if (is_arm)
	{
		o << "    .globl _main\n";
		o << "    .p2align 2\n";
		o << "_main:\n";
		int total = -nextFreeSymbolIndex;
		if (total % 16 != 0)
			total += (16 - (total % 16));
		stack_allocation = total;

		o << "    sub sp, sp, #" << total << "\n";

		currentST_index = 1;
		for (auto bb : bbs)
		{
			for (auto instr : bb->instrs)
			{
				instr->gen_asm_arm(o);
			}
		}

		return;
	}

	// X86 fallback
#ifdef __APPLE__
	o << ".globl _main\n";
	o << "_main:\n";
#else
	o << ".globl main\n";
	o << "main:\n";
#endif

	gen_asm_prologue(o);

	currentST_index = 1;
	for (auto bb : bbs)
	{
		bb->gen_asm(o);
	}

	gen_asm_epilogue(o);
}

// ---------- IRGenerator ----------
class IRGenerator : public ifccBaseVisitor
{
public:
	IRGenerator(CFG *cfg_) : cfg(cfg_)
	{
		BasicBlock *current_bb = new BasicBlock(cfg, "entry");
		cfg->current_bb = current_bb;
		cfg->add_bb(current_bb);
	}

	// antlrcpp::Any visitFunction(ifccParser::FunctionContext *ctx) override {
	// 	auto stmts = ctx->block()->stmt();
	// 	for (auto stmt : stmts) {
	// 		this->visit(stmt);

	// 		// early return: si on a déjà rencontré 'ret'
	// 		if (!cfg->current_bb->instrs.empty()) {
	// 			IRInstr *last = cfg->current_bb->instrs.back();
	// 			if (last->getOperation() == IRInstr::ret) {
	// 				break;
	// 			}
	// 		}
	// 	}
	// 	return 0;
	// }

	antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override
	{
		// Si c’est une constante, on la renvoie directement
		if (auto constExpr = dynamic_cast<ifccParser::ConstExprContext *>(ctx->expr()))
		{
			std::string value = constExpr->CONST()->getText();
			cfg->current_bb->add_IRInstr(IRInstr::ret, INT, {"$" + value});
		}
		else
		{
			std::string temp = visit(ctx->expr()).as<std::string>();
			cfg->current_bb->add_IRInstr(IRInstr::ret, INT, {temp});
		}

		return 0;
	}

	antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override
	{
		std::string varName = ctx->VAR()->getText();

		if (ctx->expr())
		{
			std::string rhs = visit(ctx->expr()).as<std::string>();
			cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {varName, rhs});
		}
		else
		{
			// Initialisation implicite à 0
			cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {varName, "0"});
		}

		return 0;
	}

	antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override
	{
		std::string varName = ctx->VAR()->getText();
		std::string rhs = visit(ctx->expr()).as<std::string>();
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {varName, rhs});
		return rhs;
	}

	antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override
	{
		return ctx->VAR()->getText();
	}

	antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) override
	{
		std::string temp = cfg->create_new_tempvar(INT);
		std::string value = ctx->CONST()->getText();
		cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {temp, value});
		return temp;
	}

	antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override
	{
		std::string lhs = visit(ctx->expr(0)).as<std::string>();
		std::string rhs = visit(ctx->expr(1)).as<std::string>();
		std::string result = cfg->create_new_tempvar(INT);

		std::string op = ctx->OP->getText();
		if (op == "+")
			cfg->current_bb->add_IRInstr(IRInstr::add, INT, {result, lhs, rhs});
		else
			cfg->current_bb->add_IRInstr(IRInstr::sub, INT, {result, lhs, rhs});

		return result;
	}

	antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) override
	{
		std::string lhs = visit(ctx->expr(0)).as<std::string>();
		std::string rhs = visit(ctx->expr(1)).as<std::string>();
		std::string result = cfg->create_new_tempvar(INT);

		std::string op = ctx->OP->getText();
		if (op == "*")
			cfg->current_bb->add_IRInstr(IRInstr::mul, INT, {result, lhs, rhs});
		else if (op == "/")
			cfg->current_bb->add_IRInstr(IRInstr::div, INT, {result, lhs, rhs});
		else if (op == "%")
			cfg->current_bb->add_IRInstr(IRInstr::mod, INT, {result, lhs, rhs});
		return result;
	}

	antlrcpp::Any visitParExpr(ifccParser::ParExprContext *ctx) override
	{
		return visit(ctx->expr());
	}

	antlrcpp::Any visitNegateExpr(ifccParser::NegateExprContext *ctx) override
	{
		std::string operand = visit(ctx->expr()).as<std::string>();
		std::string zero = cfg->create_new_tempvar(INT);
		cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {zero, "0"});

		std::string result = cfg->create_new_tempvar(INT);
		cfg->current_bb->add_IRInstr(IRInstr::sub, INT, {result, zero, operand});
		return result;
	}

	antlrcpp::Any visitNotExpr(ifccParser::NotExprContext *ctx) override
	{
		std::string expr = visit(ctx->expr()).as<std::string>();
		std::string zero = cfg->create_new_tempvar(INT);
		cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {zero, "0"});

		std::string cmp = cfg->create_new_tempvar(INT);
		cfg->current_bb->add_IRInstr(IRInstr::cmp_eq, INT, {cmp, expr, zero});
		return cmp;
	}

	antlrcpp::Any visitCmpExpr(ifccParser::CmpExprContext *ctx) override
	{
		std::string lhs = visit(ctx->expr(0)).as<std::string>();
		std::string rhs = visit(ctx->expr(1)).as<std::string>();
		std::string result = cfg->create_new_tempvar(INT);
		int lhsType = cfg->get_var_type(lhs);
		int rhsType = cfg->get_var_type(rhs);

		// // Utilise le getter pour accéder au SymbolType
		// map<string, Type> &symbolTypes = cfg->getSymbolType();

		// Type lhsType = symbolTypes.count(lhs) ? symbolTypes[lhs] : INT;
		// Type rhsType = symbolTypes.count(rhs) ? symbolTypes[rhs] : INT;
		Type effectiveType = (lhsType == CHAR || rhsType == CHAR) ? CHAR : INT;

		std::string op = ctx->getText();

		if (op.find("==") != string::npos)
			cfg->current_bb->add_IRInstr(IRInstr::cmp_eq, effectiveType, {result, lhs, rhs});
		else if (op.find("!=") != string::npos)
		{
			std::string tmp = cfg->create_new_tempvar(effectiveType);
			cfg->current_bb->add_IRInstr(IRInstr::cmp_eq, effectiveType, {tmp, lhs, rhs});
			cfg->current_bb->add_IRInstr(IRInstr::ldconst, effectiveType, {result, "1"});
			cfg->current_bb->add_IRInstr(IRInstr::sub, effectiveType, {result, result, tmp});
		}
		else if (op.find("<=") != string::npos)
			cfg->current_bb->add_IRInstr(IRInstr::cmp_le, effectiveType, {result, lhs, rhs});
		else if (op.find(">=") != string::npos)
			cfg->current_bb->add_IRInstr(IRInstr::cmp_ge, effectiveType, {result, lhs, rhs});
		else if (op.find("<") != string::npos)
			cfg->current_bb->add_IRInstr(IRInstr::cmp_lt, effectiveType, {result, lhs, rhs});
		else if (op.find(">") != string::npos)
			cfg->current_bb->add_IRInstr(IRInstr::cmp_lt, effectiveType, {result, rhs, lhs});

		return result;
	}

	antlrcpp::Any visitCharConstExpr(ifccParser::CharConstExprContext *ctx) override
	{
		std::string temp = cfg->create_new_tempvar(CHAR);
		std::string text = ctx->CHAR()->getText(); // exemple : 'A'
		char c = text[1];						   // le caractère réel entre les apostrophes
		int asciiValue = static_cast<int>(c);
		cfg->current_bb->add_IRInstr(IRInstr::ldconst, CHAR, {temp, std::to_string(asciiValue)});
		return temp;
	}

	antlrcpp::Any visitBitwiseAndExpr(ifccParser::BitwiseAndExprContext *ctx) override
	{
		std::string lhs = visit(ctx->expr(0)).as<std::string>();
		std::string rhs = visit(ctx->expr(1)).as<std::string>();
		std::string result = cfg->create_new_tempvar(INT);
		cfg->current_bb->add_IRInstr(IRInstr::bitwise_and, INT, {result, lhs, rhs});
		return result;
	}

	antlrcpp::Any visitBitwiseOrExpr(ifccParser::BitwiseOrExprContext *ctx) override
	{
		std::string lhs = visit(ctx->expr(0)).as<std::string>();
		std::string rhs = visit(ctx->expr(1)).as<std::string>();
		std::string result = cfg->create_new_tempvar(INT);
		cfg->current_bb->add_IRInstr(IRInstr::bitwise_or, INT, {result, lhs, rhs});
		return result;
	}

	antlrcpp::Any visitBitwiseXorExpr(ifccParser::BitwiseXorExprContext *ctx) override
	{
		std::string lhs = visit(ctx->expr(0)).as<std::string>();
		std::string rhs = visit(ctx->expr(1)).as<std::string>();
		std::string result = cfg->create_new_tempvar(INT);
		cfg->current_bb->add_IRInstr(IRInstr::bitwise_xor, INT, {result, lhs, rhs});
		return result;
	}

	antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx)
	{
		// BasicBlock *current_bb = new BasicBlock(cfg, "label");
		// current_bb->parent = cfg->current_bloc_index;
		// cfg->add_bb(current_bb);
		// int parent_index = cfg->current_bloc_index;

		cfg->last_ST_index += 1;
		int parentST_index = cfg->currentST_index;
		cfg->currentST_index = cfg->last_ST_index;
		for (auto stmt : ctx->stmt())
		{					   // iterate over each statement in the list
			this->visit(stmt); // visit each statement (declaration, assignment, return)
		}
		cfg->currentST_index = parentST_index;
		return 0;
	}

private:
	CFG *cfg;
};