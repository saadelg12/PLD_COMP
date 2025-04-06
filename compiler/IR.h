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
		ldvar,
		copy,
		add,
		sub,
		mul,
		div,
		mod,
		neg,
		cmp_eq,
		cmp_expr,
		cmp_lt,
		cmp_le,
		cmp_ge,
		bitwise_and,
		bitwise_or,
		bitwise_xor,
		ret,
		cond_jump,
		call,
		jump
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
	BasicBlock *exit = nullptr;
	string test_var_name;
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

	string IR_reg_to_asm(string param) const {
		// Si c'est un offset explicite (ex: "-4"), on le traite directement
		if (std::all_of(param.begin(), param.end(), [](char c) { return std::isdigit(c) || c == '-'; })) {
			int offset = std::stoi(param);
			if (is_arm)
				return "[sp, #" + to_string(-offset) + "]"; // ARM utilise des offsets positifs
			else
				return to_string(offset) + "(%rbp)";        // X86 utilise des offsets négatifs
		}
	
		// Sinon, c'est un nom de variable ou de temporaire, on cherche son offset dans la symbol table
		int offset = get_var_index(param);
		if (is_arm)
			return "[sp, #" + to_string(-offset) + "]";
		else
			return to_string(offset) + "(%rbp)";
	}
	

	int get_var_index(const string &name) const
	{
		// cout<< "looking for  "<<name<< " IN  "<<currentST_index<<endl;
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
		// On utilise directement l'offset actuel
		int offset = nextFreeSymbolIndex;

		// On enregistre ce symbole dans la table, même si on n'utilise plus son nom
		Symbol s;
		s.symbolName = to_string(offset); // utile uniquement pour traçage/debug éventuel
		s.symbolOffset = offset;
		s.symbolType = t;
		symbolTable.at(currentST_index)->table[s.symbolName] = s;

		nextFreeSymbolIndex -= 4;

		// On retourne l'offset en string pour l'utiliser directement dans l'IR
		return to_string(offset);
	}


	int currentST_index;
	int last_ST_index;
	vector<BasicBlock *> bbs;
	vector<SymbolTable *> symbolTable;
	BasicBlock *current_bb;
	int nextFreeSymbolIndex;

	bool is_arm = false;	  // false = x86, true = ARM
	int stack_allocation = 0; // Allocation pour décalage de sp

private:
	void *ast;
};

// ---------- ASSEMBLEUR POUR IRInstr ----------
void IRInstr::gen_asm(ostream &o)
{

	string s = suffix_for_type(t); // suffix for instruction based on type
	string dst;

	// if (op != ret)
	// {
	// 	dst = bb->cfg->IR_reg_to_asm(params[0]);
	// }

	switch (op)
	{
	case ldconst:
		o << "    mov" << s << " $" << params[0] << ", %eax\n";
		break;

	case ldvar:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		break;

	case copy:
		o << "    mov" << s << " %eax, " << params[0] << "(%rbp)\n";
		break;

	case add:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    add" << s << " " << params[1] << "(%rbp), %eax\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case sub:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    sub" << s << " " << params[1] << "(%rbp), %eax\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case mul:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    imul" << s << " " << params[1] << "(%rbp), %eax\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case div:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    cltd\n";
		o << "    idiv" << s << " " << params[1] << "(%rbp)\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case mod:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    cltd\n";
		o << "    idiv" << s << " " << params[1] << "(%rbp)\n";
		o << "    mov" << s << " %edx, %eax \n";
		break;
	case neg:
		o << "    neg" << s << " %eax\n";
		break;
	case cmp_eq:
		o << "    cmp" << s << " $0, %eax\n";
		o << "    mov" << s << " $0, %eax\n";
		o << "    sete %al\n";
		break;

	case cmp_expr:
		o << "    cmp" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    " << params[1] << " %al\n";
		o << "    movzbl %al, %eax\n";
		break;

	case cmp_lt:
		if (t == CHAR)
		{
			o << "    movb " << params[1] << ", %al\n";
			o << "    cmpb " << params[2] << ", %al\n";
		}
		else
		{
			o << "    movl " << params[1] << ", %eax\n";
			o << "    cmpl " << params[2] << ", %eax\n";
		}
		o << "    setl %al\n";
		o << "    movzbl %al, %eax\n";
		o << "    movl %eax, " << params[0] << "\n";
		break;

	case cmp_le:
		if (t == CHAR)
		{
			o << "    movb " << params[1] << ", %al\n";
			o << "    cmpb " << params[2] << ", %al\n";
		}
		else
		{
			o << "    movl " << params[1] << ", %eax\n";
			o << "    cmpl " << params[2] << ", %eax\n";
		}
		o << "    setle %al\n";
		o << "    movzbl %al, %eax\n";
		o << "    movl %eax, " << params[0] << "\n";
		break;

	case cmp_ge:
		if (t == CHAR)
		{
			o << "    movb " << params[1] << ", %al\n";
			o << "    cmpb " << params[2] << ", %al\n";
		}
		else
		{
			o << "    movl " << params[1] << ", %eax\n";
			o << "    cmpl " << params[2] << ", %eax\n";
		}
		o << "    setge %al\n";
		o << "    movzbl %al, %eax\n";
		o << "    movl %eax, " << params[0] << "\n";
		break;

	case bitwise_and:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    and" << s << " " << params[1] << "(%rbp), %eax\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case bitwise_or:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    or" << s << " " << params[1] << "(%rbp), %eax\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case bitwise_xor:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    xor" << s << " " << params[1] << "(%rbp), %eax\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case ret:
	{
		o << "    leave\n";
		o << "    ret\n";
		break;
	}
	case cond_jump:
	{
		o << "    test" << s << " %eax, %eax\n  ";
		o << "    jz " << params[1] << "\n";  // 3. Saute si ZF=1 (valeur était 0)   ;
		o << "    jnz " << params[0] << "\n"; // 3. Saute si ZF=0 (valeur était différente de 0)   ;
		break;
	}
	case jump:
	{
		o << "    jmp " << params[0] << "\n";
	}
	
	case call:
	{
		const std::string& funcName = params[0];

		if (funcName == "putchar") {
			std::string arg = bb->cfg->IR_reg_to_asm(params[1]);
			o << "    movl " << arg << ", %edi\n";
			o << "    call putchar\n";
		}
		else if (funcName == "getchar") {
			std::string dst = bb->cfg->IR_reg_to_asm(params[1]);
			o << "    call getchar\n";
			o << "    movl %eax, " << dst << "\n";
		}
		break;
	}


	default:
		break;
	}
}

void IRInstr::gen_asm_arm(std::ostream &o)
{
	string s = suffix_for_type(t);
	string dst;

	switch (op)
	{
	case ldconst:
		o << "    mov w0, #" << params[0] << "\n";
		break;

	case ldvar:
		o << "    ldr w0, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		break;

	case copy:
		o << "    str w0, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		break;

	case add:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    add w0, w1, w2\n";
		break;

	case sub:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    sub w0, w1, w2\n";
		break;

	case mul:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    mul w0, w1, w2\n";
		break;

	case div:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    sdiv w0, w1, w2\n";
		break;

	case mod:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    sdiv w3, w1, w2\n";
		o << "    msub w0, w3, w2, w1\n"; // mod = a - (a / b) * b
		break;

	case neg:
		o << "    neg w0, w0\n";
		break;

	case cmp_eq:
		o << "    cmp w0, #0\n";
		o << "    cset w0, eq\n";
		break;

	case cmp_expr:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    cmp w0, w1\n";
		if (params[1] == "sete")
			o << "    cset w0, eq\n";
		else if (params[1] == "setne")
			o << "    cset w0, ne\n";
		else if (params[1] == "setlt" || params[1] == "setl")
			o << "    cset w0, lt\n";
		else if (params[1] == "setle")
			o << "    cset w0, le\n";
		else if (params[1] == "setge")
			o << "    cset w0, ge\n";
		else if (params[1] == "setg")
			o << "    cset w0, gt\n";
		break;

	case cmp_lt:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    cmp w1, w2\n";
		o << "    cset w0, lt\n";
		o << "    str w0, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		break;

	case cmp_le:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    cmp w1, w2\n";
		o << "    cset w0, le\n";
		o << "    str w0, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		break;

	case cmp_ge:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    cmp w1, w2\n";
		o << "    cset w0, ge\n";
		o << "    str w0, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		break;

	case bitwise_and:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    and w0, w1, w2\n";
		break;

	case bitwise_or:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    orr w0, w1, w2\n";
		break;

	case bitwise_xor:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    eor w0, w1, w2\n";
		break;

	case ret:
		o << "    add sp, sp, #" << bb->cfg->stack_allocation << "\n";
		o << "    ret\n";
		break;

	case cond_jump:
		o << "    cmp w0, #0\n";
		o << "    b.eq " << params[1] << "\n";
		o << "    b " << params[0] << "\n";
		break;

	case jump:
		o << "    b " << params[0] << "\n";
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
	o << this->label << ":\n";
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
	o << "    subq $64, %rsp\n";
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
			bb->gen_asm(o); // Ça imprime les labels et les instructions
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

	// gen_asm_epilogue(o);
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

	antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override
	{
		visit(ctx->expr());
		cfg->current_bb->add_IRInstr(IRInstr::ret, INT, {});
		return 0;
	}

	antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override
	{
		// cout<<"visitDeclaration\n";
		std::string varName = ctx->VAR()->getText();
		string offset = to_string(cfg->get_var_index(varName));
		Type type = cfg->get_var_type(varName);
		if (ctx->expr())
		{
			visit(ctx->expr());
		}
		else
		{
			// Initialisation implicite à 0
			cfg->current_bb->add_IRInstr(IRInstr::ldvar, type, {"0"});
		}
		cfg->current_bb->add_IRInstr(IRInstr::copy, type, {offset});
		return 0;
	}

	antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override
	{
		// cout<<"visitAssignment\n";
		std::string varName = ctx->VAR()->getText();
		string offset = to_string(cfg->get_var_index(varName));
		Type type = cfg->get_var_type(varName);
		// std::string rhs = any_cast<std::string>(visit(ctx->expr()));
		// string rhsOffset =  to_string(cfg->get_var_index(rhs)) + "(%rbp)";
		antlrcpp::Any value = visit(ctx->expr());
		// cout<<" varName" <<varName<<rhs <<"rhs "<< rhs<< endl ;
		cfg->current_bb->add_IRInstr(IRInstr::copy, type, {offset});
		return value;
	}

	antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override
	{
		// return ctx->VAR()->getText();
		std::string varName = ctx->VAR()->getText();
		string offset = to_string(cfg->get_var_index(varName));
		Type type = cfg->get_var_type(varName);
		cfg->current_bb->add_IRInstr(IRInstr::ldvar, type, {offset});
		return 0;
	}

	antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) override
	{
		// std::string temp = cfg->create_new_tempvar(INT);
		// string offset =  to_string(cfg->get_var_index(temp))+ "(%rbp)";
		std::string value = ctx->CONST()->getText();
		cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {value});
		return 0;
	}

	antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override
	{
		// cout<<"visitAddSub\n";
		visit(ctx->expr(0));
		cfg->nextFreeSymbolIndex -= 4;
		string leftOffset = to_string(cfg->nextFreeSymbolIndex);
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
		visit(ctx->expr(1));
		cfg->nextFreeSymbolIndex -= 4;
		string rightOffset = to_string(cfg->nextFreeSymbolIndex);
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});

		std::string op = ctx->OP->getText();
		if (op == "+")
			cfg->current_bb->add_IRInstr(IRInstr::add, INT, {leftOffset, rightOffset});
		else
			cfg->current_bb->add_IRInstr(IRInstr::sub, INT, {leftOffset, rightOffset});

		return 0;
	}

	antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) override
	{
		// cout<<"visitMulDiv\n";
		visit(ctx->expr(0));
		cfg->nextFreeSymbolIndex -= 4;
		string leftOffset = to_string(cfg->nextFreeSymbolIndex);
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
		visit(ctx->expr(1));
		cfg->nextFreeSymbolIndex -= 4;
		string rightOffset = to_string(cfg->nextFreeSymbolIndex);
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
		std::string op = ctx->OP->getText();
		if (op == "*")
		{
			cfg->current_bb->add_IRInstr(IRInstr::mul, INT, {leftOffset, rightOffset});
		}
		else if (op == "/")
		{
			cfg->current_bb->add_IRInstr(IRInstr::div, INT, {leftOffset, rightOffset});
		}
		else if (op == "%")
		{
			cfg->current_bb->add_IRInstr(IRInstr::mod, INT, {leftOffset, rightOffset});
		}
		return 0;
	}

	antlrcpp::Any visitParExpr(ifccParser::ParExprContext *ctx) override
	{
		// cout<<"visitParExpr\n";
		return visit(ctx->expr());
	}

	antlrcpp::Any visitNegateExpr(ifccParser::NegateExprContext *ctx) override
	{
		// cout<<"visitNegateExpr\n";
		visit(ctx->expr());
		cfg->current_bb->add_IRInstr(IRInstr::neg, INT, {});
		return 0;
	}

	antlrcpp::Any visitNotExpr(ifccParser::NotExprContext *ctx) override
	{
		visit(ctx->expr());
		cfg->current_bb->add_IRInstr(IRInstr::cmp_eq, INT, {});
		return 0;
	}

	antlrcpp::Any visitCmpExpr(ifccParser::CmpExprContext *ctx) override
	{
		visit(ctx->expr(0));
		cfg->nextFreeSymbolIndex -= 4;
		string leftOffset = to_string(cfg->nextFreeSymbolIndex);
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
		visit(ctx->expr(1));
		cfg->nextFreeSymbolIndex -= 4;
		string rightOffset = to_string(cfg->nextFreeSymbolIndex);

		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
		cfg->current_bb->add_IRInstr(IRInstr::ldvar, INT, {leftOffset});

		std::string op = ctx->getText();
		std::string setInstr;

		if (op.find("==") != std::string::npos)
			setInstr = "sete";
		else if (op.find("!=") != std::string::npos)
			setInstr = "setne";
		else if (op.find("<=") != std::string::npos)
			setInstr = "setle";
		else if (op.find(">=") != std::string::npos)
			setInstr = "setge";
		else if (op.find("<") != std::string::npos)
			setInstr = "setl";
		else if (op.find(">") != std::string::npos)
			setInstr = "setg";

		cfg->current_bb->add_IRInstr(IRInstr::cmp_expr, INT, {rightOffset, setInstr});

		return 0;
	}

	antlrcpp::Any visitCharConstExpr(ifccParser::CharConstExprContext *ctx) override
	{

		std::string text = ctx->CHAR()->getText(); // exemple : 'A'
		char c = text[1];						   // le caractère réel entre les apostrophes
		string asciiValue = to_string(static_cast<int>(c));
		cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {asciiValue});
		return 0;
	}

	antlrcpp::Any visitBitwiseAndExpr(ifccParser::BitwiseAndExprContext *ctx) override
	{
		visit(ctx->expr(0));
		cfg->nextFreeSymbolIndex -= 4;
		string leftOffset = to_string(cfg->nextFreeSymbolIndex);
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
		visit(ctx->expr(1));
		cfg->nextFreeSymbolIndex -= 4;
		string rightOffset = to_string(cfg->nextFreeSymbolIndex);
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
		cfg->current_bb->add_IRInstr(IRInstr::bitwise_and, INT, {leftOffset, rightOffset});
		return 0;
	}

	antlrcpp::Any visitBitwiseOrExpr(ifccParser::BitwiseOrExprContext *ctx) override
	{
		visit(ctx->expr(0));
		cfg->nextFreeSymbolIndex -= 4;
		string leftOffset = to_string(cfg->nextFreeSymbolIndex);
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
		visit(ctx->expr(1));
		cfg->nextFreeSymbolIndex -= 4;
		string rightOffset = to_string(cfg->nextFreeSymbolIndex);
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
		cfg->current_bb->add_IRInstr(IRInstr::bitwise_or, INT, {leftOffset, rightOffset});
		return 0;
	}

	antlrcpp::Any visitBitwiseXorExpr(ifccParser::BitwiseXorExprContext *ctx) override
	{
		visit(ctx->expr(0));
		cfg->nextFreeSymbolIndex -= 4;
		string leftOffset = to_string(cfg->nextFreeSymbolIndex);
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
		visit(ctx->expr(1));
		cfg->nextFreeSymbolIndex -= 4;
		string rightOffset = to_string(cfg->nextFreeSymbolIndex);
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
		cfg->current_bb->add_IRInstr(IRInstr::bitwise_xor, INT, {leftOffset, rightOffset});
		return 0;
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
		{
			this->visit(stmt);
		}
		cfg->currentST_index = parentST_index;
		if (cfg->current_bb->exit)
		{
			cfg->current_bb->add_IRInstr(IRInstr::jump, INT, {cfg->current_bb->exit->label});
		}

		return 0;
	}

	antlrcpp::Any visitIf_stmt(ifccParser::If_stmtContext *ctx)
	{
		
		//if (truc = true ) : jump vers le if bloc sinon vers le else bloc
		// cfg->current_bb->test_var_name = any_cast<std::string>(visit(ctx->expr()));
		// string offset =  to_string(cfg->get_var_index(cfg->current_bb->test_var_name))+ "(%rbp)";
		visit(ctx->expr());
		int bbs_size = cfg->bbs.size();

		std::string if_label ="label" + to_string(bbs_size);
		BasicBlock * true_exit_bb = new BasicBlock(cfg, if_label);
		BasicBlock * previous_bb = cfg->current_bb;
		cfg->current_bb->exit_true = true_exit_bb;
		cfg->current_bb = true_exit_bb;
		cfg->add_bb(true_exit_bb);
		
		
		if (ctx->block(1))
		{
			bbs_size = cfg->bbs.size();
			string else_label = "label" + to_string(bbs_size);
			BasicBlock * false_exit_bb = new BasicBlock(cfg, else_label);
			previous_bb->exit_false = false_exit_bb;
			cfg->add_bb(false_exit_bb);
			
		}
		else{
			previous_bb->exit_false = nullptr;
		}
		bbs_size = cfg->bbs.size();
		string next_label = "label" + to_string(bbs_size);
		BasicBlock * next_bb = new BasicBlock(cfg, next_label);
		cfg->add_bb(next_bb);

		previous_bb->exit_true->exit = next_bb;
		if(previous_bb->exit_false) {previous_bb->exit_false->exit = next_bb;}
		next_bb->exit = previous_bb->exit;
		
		visit(ctx->block(0));
		if(previous_bb->exit_false){
			cfg->current_bb = previous_bb->exit_false;
			visit(ctx->block(1));
		}
		
		cfg->current_bb = next_bb;
		
		std::string else_or_next_label;
		if(previous_bb->exit_false){
			else_or_next_label = previous_bb->exit_false->label;
		}else{
			 else_or_next_label = next_bb->label;
		}
		
		previous_bb->add_IRInstr(IRInstr::cond_jump, INT, {if_label,else_or_next_label});
		
		
		return 0;
	}

	antlrcpp::Any visitWhile_stmt(ifccParser::While_stmtContext *ctx)
	{
		
		int bbs_size = cfg->bbs.size();
		std::string condition_bb_label ="label" + to_string(bbs_size);
		BasicBlock * condition_bb = new BasicBlock(cfg, condition_bb_label);
		cfg->add_bb(condition_bb);
		bbs_size = cfg->bbs.size();
		std::string bb_true__label ="label" + to_string(bbs_size);
		BasicBlock * bb_true = new BasicBlock(cfg, bb_true__label);
		cfg->add_bb(bb_true);
		bbs_size = cfg->bbs.size();
		std::string bb_false_label ="label" + to_string(bbs_size);
		BasicBlock * bb_false = new BasicBlock(cfg, bb_false_label);
		cfg->add_bb(bb_false);
		condition_bb->exit_true = bb_true;
		condition_bb->exit_false = bb_false;
		bb_false->exit = cfg->current_bb->exit;
		bb_true->exit = condition_bb;
		cfg->current_bb->exit = condition_bb;
		cfg->current_bb->add_IRInstr(IRInstr::jump, INT, {condition_bb_label});
		cfg->current_bb = condition_bb;
		visit(ctx->expr());
		cfg->current_bb->add_IRInstr(IRInstr::cond_jump, INT, {bb_true__label,bb_false_label});

		cfg->current_bb = bb_true;
		visit(ctx->block());
		cfg->current_bb = bb_false;


		return 0;
	}

	antlrcpp::Any visitFunction_call(ifccParser::Function_callContext *ctx) override {
		std::string funcName = ctx->VAR()->getText();
	
		if (funcName == "putchar") {
			visit(ctx->expr(0));  // Place l'argument dans %eax
	
			std::string temp = cfg->create_new_tempvar(INT);   // Crée une var temporaire
			cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {temp}); // Sauvegarde %eax
			cfg->current_bb->add_IRInstr(IRInstr::call, INT, {"putchar", temp});
			return 0;
		}
		else if (funcName == "getchar") {
			std::string temp = cfg->create_new_tempvar(INT);
			cfg->current_bb->add_IRInstr(IRInstr::call, INT, {"getchar", temp});
			return temp;
		}
	
		return 0;
	}	

private:
	CFG *cfg;
};
