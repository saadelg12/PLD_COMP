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
		neg,
		cmp_eq,
		cmp_expr,
		cmp_lt,
		cmp_le,
		cmp_ge,
		bitwise_and,
		bitwise_or,
		bitwise_xor,
		call,
		ret,
		cond_jump,
		jump
	};

	IRInstr(BasicBlock *bb_, Operation op, Type t, vector<string> params)
		: bb(bb_), op(op), t(t), params(params) {}

	Operation getOperation() const { return op; }

	void gen_asm(ostream &o);

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

	void add_bb(BasicBlock *bb) { bbs.push_back(bb);}

	void gen_asm(ostream &o);
	void gen_asm_prologue(ostream &o);
	void gen_asm_epilogue(ostream &o);

	string IR_reg_to_asm(const string &reg) const
	{
		return to_string(get_var_index(reg)) + "(%rbp)";
	}

	int get_var_index(const string &name) const
	{
		//cout<< "looking for  "<<name<< " IN  "<<currentST_index<<endl;
		SymbolTable * current_symbol_table = symbolTable.at(currentST_index);
		int res = current_symbol_table->get(name).symbolOffset;
		return res;
	}
	Type get_var_type(const string &name) const
	{
		SymbolTable * current_symbol_table = symbolTable.at(currentST_index);
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
		//cout<< "creating "<<name<< " IN  "<<currentST_index<<endl;
		nextFreeSymbolIndex -= 4;
		
		return name;
	}
	
	

	
	int currentST_index;
	int last_ST_index;
	vector<BasicBlock *> bbs;
	vector<SymbolTable *> symbolTable;
	BasicBlock * current_bb;
	int nextFreeSymbolIndex;
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
		//o << "    mov" << s << " $" << params[1] << ", " << params[0] << "\n";
		o << "    mov" << s <<" " << params[0] << ", %eax\n";
		break;

	case copy:
		//o << "    mov" << s << " " << params[1] << ", %eax\n";
		o << "    mov" <<s << " %eax, " << params[0] << "\n";
		break;

	case add:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    add" << s << " " << params[1] << ", %eax\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case sub:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    sub" << s << " " << params[1] << ", %eax\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case mul:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    imul" << s << " " << params[1] << ", %eax\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case div:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    cltd\n";
		o << "    idiv" << s << " " << params[1] << "\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case mod:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    cltd\n";
		o << "    idiv" << s << " " << params[1] << "\n";
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
	o << "    cmp" << s << " "<<params[0]<<", %eax\n";
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
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    and" << s << " " << params[1] << ", %eax\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case bitwise_or:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    or" << s << " " << params[1] << ", %eax\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case bitwise_xor:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    xor" << s << " " << params[1] << ", %eax\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

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

	case ret:
	{
		// const string &src = params[0];
		// if (!src.empty() && src[0] == '$')
		// {
		// 	o << "    movl " << src << ", %eax\n";
		// }
		// else
		// {
		// 	o << "    mov" << s << " " << src << ", %eax\n";
		// 	if (s == "b")
		// 	{
		// 		o << "    movzbl %al, %eax\n"; // étend 8 bits → 32 bits
		// 	}
		// }
		o << "    leave\n";  
    	o << "    ret\n";       
		break;
	}
	case cond_jump:
	{
		//o << "    movl " << params[0] << ", %eax\n";  // Charge la valeur à tester
		o << "    test"<<s<<" %eax, %eax\n  ";
		o << "    jz "<<params[1]<<"\n";            //3. Saute si ZF=1 (valeur était 0)   ; 
		o << "    jnz "<<params[0]<<"\n";            //3. Saute si ZF=0 (valeur était différente de 0)   ; 
		break;
	}
	case jump:
	{
		o << "    jmp " << params[0] << "\n";
	}

	default:
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

void CFG::gen_asm(ostream &o)
{
#ifdef __APPLE__
	o << ".globl _main\n";
	o << "_main:\n";
#else
	o << ".globl main\n";
	o << "main:\n";
#endif
	gen_asm_prologue(o);
	currentST_index = 1;
	for (auto bb : bbs) {
    	bb->gen_asm(o);
	}
	//gen_asm_epilogue(o);
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
		// if (auto constExpr = dynamic_cast<ifccParser::ConstExprContext *>(ctx->expr()))
		// {
		// 	std::string value = constExpr->CONST()->getText();
		// 	cfg->current_bb->add_IRInstr(IRInstr::ret, INT, {"$" + value});
		// }
		// else
		// {
        // 	std::string temp = std::any_cast<std::string>(visit(ctx->expr()));
		// 	string offset =  to_string(cfg->get_var_index(temp)) + "(%rbp)";
		// 	cfg->current_bb->add_IRInstr(IRInstr::ret, INT, {offset});
		// }
		visit(ctx->expr());
		cfg->current_bb->add_IRInstr(IRInstr::ret,INT,{});
		return 0;
	}

	antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override
	{
		//cout<<"visitDeclaration\n";
		std::string varName = ctx->VAR()->getText();
		string offset =  to_string(cfg->get_var_index(varName))+ "(%rbp)";
		Type type =  cfg->get_var_type(varName);
		if (ctx->expr())
		{
			//std::string rhs = any_cast<std::string>(visit(ctx->expr()));
			//string rhsOffset =  to_string(cfg->get_var_index(rhs)) + "(%rbp)";
			visit(ctx->expr());
			
		}
		else
		{
			// Initialisation implicite à 0
			cfg->current_bb->add_IRInstr(IRInstr::ldconst, type, {"$0"});
		}
		cfg->current_bb->add_IRInstr(IRInstr::copy, type, {offset});
		return 0;
	}
	
	antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override
	{
		//cout<<"visitAssignment\n";
		std::string varName = ctx->VAR()->getText();
		string offset =  to_string(cfg->get_var_index(varName)) + "(%rbp)";
		Type type =  cfg->get_var_type(varName);
		// std::string rhs = any_cast<std::string>(visit(ctx->expr()));
		// string rhsOffset =  to_string(cfg->get_var_index(rhs)) + "(%rbp)";
		antlrcpp::Any value = visit(ctx->expr());
		//cout<<" varName" <<varName<<rhs <<"rhs "<< rhs<< endl ;
		cfg->current_bb->add_IRInstr(IRInstr::copy, type, {offset});
		return value;
	}

	antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override
	{
		//return ctx->VAR()->getText();
		std::string varName = ctx->VAR()->getText();
    	string offset =  to_string(cfg->get_var_index(varName)) + "(%rbp)";
		Type type =  cfg->get_var_type(varName);
		cfg->current_bb->add_IRInstr(IRInstr::ldconst, type, {offset});
		return 0;
	}

	antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) override
	{
		// std::string temp = cfg->create_new_tempvar(INT);
		// string offset =  to_string(cfg->get_var_index(temp))+ "(%rbp)";
		std::string value = "$"+ ctx->CONST()->getText();
		cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {value});
		return 0;
	}

	antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override
	{
		//cout<<"visitAddSub\n";
		visit(ctx->expr(0));  
		cfg->nextFreeSymbolIndex -= 4;
		string leftOffset =  to_string(cfg->nextFreeSymbolIndex)+ "(%rbp)";
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
		visit(ctx->expr(1));
		cfg->nextFreeSymbolIndex -= 4;
		string rightOffset =  to_string(cfg->nextFreeSymbolIndex)+ "(%rbp)";
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});

		
		std::string op = ctx->OP->getText();
		if (op == "+")
			cfg->current_bb->add_IRInstr(IRInstr::add, INT, {leftOffset,rightOffset});
		else
			cfg->current_bb->add_IRInstr(IRInstr::sub, INT, {leftOffset, rightOffset});

		return 0;
	}

	antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) override
	{
		//cout<<"visitMulDiv\n";
		visit(ctx->expr(0));  
		cfg->nextFreeSymbolIndex -= 4;
		string leftOffset =  to_string(cfg->nextFreeSymbolIndex)+ "(%rbp)";
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
		visit(ctx->expr(1));
		cfg->nextFreeSymbolIndex -= 4;
		string rightOffset =  to_string(cfg->nextFreeSymbolIndex)+ "(%rbp)";
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
		std::string op = ctx->OP->getText();
		if (op == "*")
			{cfg->current_bb->add_IRInstr(IRInstr::mul, INT, {leftOffset,rightOffset});}
		else if (op == "/")
			{cfg->current_bb->add_IRInstr(IRInstr::div, INT, {leftOffset,rightOffset});}
		else if (op == "%")
			{cfg->current_bb->add_IRInstr(IRInstr::mod, INT, {leftOffset,rightOffset});}
		return 0;
	}

	antlrcpp::Any visitParExpr(ifccParser::ParExprContext *ctx) override
	{
		//cout<<"visitParExpr\n";
		return visit(ctx->expr());
	}

	antlrcpp::Any visitNegateExpr(ifccParser::NegateExprContext *ctx) override
	{
		//cout<<"visitNegateExpr\n";
		visit(ctx->expr());
		cfg->current_bb->add_IRInstr(IRInstr::neg, INT,{});
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
		string leftOffset =  to_string(cfg->nextFreeSymbolIndex)+ "(%rbp)";
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
		visit(ctx->expr(1));
		cfg->nextFreeSymbolIndex -= 4;
		string rightOffset =  to_string(cfg->nextFreeSymbolIndex)+ "(%rbp)";
		
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
		cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {leftOffset});

		std::string op = ctx->getText();
		std::string setInstr;

		if (op.find("==") != std::string::npos)      setInstr = "sete";
		else if (op.find("!=") != std::string::npos) setInstr = "setne";
		else if (op.find("<=") != std::string::npos) setInstr = "setle";
		else if (op.find(">=") != std::string::npos) setInstr = "setge";
		else if (op.find("<") != std::string::npos)  setInstr = "setl";
		else if (op.find(">") != std::string::npos)  setInstr = "setg";

		
		cfg->current_bb->add_IRInstr(IRInstr::cmp_expr, INT, {rightOffset,setInstr});

		

		return 0;
	}

	antlrcpp::Any visitCharConstExpr(ifccParser::CharConstExprContext *ctx) override
	{
		
		std::string text = ctx->CHAR()->getText(); // exemple : 'A'
		char c = text[1];						   // le caractère réel entre les apostrophes
		string asciiValue = " $"+to_string(static_cast<int>(c));
		cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {asciiValue});
		return 0;
	}

	
	antlrcpp::Any visitBitwiseAndExpr(ifccParser::BitwiseAndExprContext *ctx) override {
		visit(ctx->expr(0));  
		cfg->nextFreeSymbolIndex -= 4;
		string leftOffset =  to_string(cfg->nextFreeSymbolIndex)+ "(%rbp)";
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
		visit(ctx->expr(1));
		cfg->nextFreeSymbolIndex -= 4;
		string rightOffset =  to_string(cfg->nextFreeSymbolIndex)+ "(%rbp)";
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
		cfg->current_bb->add_IRInstr(IRInstr::bitwise_and, INT, {leftOffset, rightOffset});
		return 0;
	}

	antlrcpp::Any visitBitwiseOrExpr(ifccParser::BitwiseOrExprContext *ctx) override {
		visit(ctx->expr(0));  
		cfg->nextFreeSymbolIndex -= 4;
		string leftOffset =  to_string(cfg->nextFreeSymbolIndex)+ "(%rbp)";
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
		visit(ctx->expr(1));
		cfg->nextFreeSymbolIndex -= 4;
		string rightOffset =  to_string(cfg->nextFreeSymbolIndex)+ "(%rbp)";
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
		cfg->current_bb->add_IRInstr(IRInstr::bitwise_or, INT, {leftOffset, rightOffset});
		return 0;
	}

	antlrcpp::Any visitBitwiseXorExpr(ifccParser::BitwiseXorExprContext *ctx) override {
		visit(ctx->expr(0));  
		cfg->nextFreeSymbolIndex -= 4;
		string leftOffset =  to_string(cfg->nextFreeSymbolIndex)+ "(%rbp)";
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
		visit(ctx->expr(1));
		cfg->nextFreeSymbolIndex -= 4;
		string rightOffset =  to_string(cfg->nextFreeSymbolIndex)+ "(%rbp)";
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
		if(cfg->current_bb->exit){cfg->current_bb->add_IRInstr(IRInstr::jump, INT, {cfg->current_bb->exit->label});}
		
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
		
		
		// if(!previous_bb->exit_true->exit_true){
		// 	previous_bb->exit_true->add_IRInstr(IRInstr::jump, INT, {new_label});
		// }
		// if(previous_bb->exit_false) {
		// 	if(!previous_bb->exit_false->exit_true){
		// 		previous_bb->exit_false->add_IRInstr(IRInstr::jump, INT, {new_label});
		// 	}
		// }
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
		std::string funcName = ctx->FUNC()->getText();
	
		if (funcName == "putchar") {
			visit(ctx->expr());  // Met la valeur dans %eax
	
			std::string temp = cfg->create_new_tempvar(INT);
			std::string offset = cfg->IR_reg_to_asm(temp);  // -4(%rbp) ou autre
			cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {offset});
	
			cfg->current_bb->add_IRInstr(IRInstr::call, INT, {"putchar", temp});
			return 0;
		}
		else if (funcName == "getchar") {
			cfg->nextFreeSymbolIndex -= 4;
			std::string dstOffset = to_string(cfg->nextFreeSymbolIndex) + "(%rbp)";
			cfg->current_bb->add_IRInstr(IRInstr::call, INT, {"getchar", dstOffset});
			// Il faut retourner dstOffset, sinon on ne peut pas le réutiliser dans l'affectation !
			return dstOffset;
		}
	
		return 0;
	}			
	

private:
	CFG *cfg;
};