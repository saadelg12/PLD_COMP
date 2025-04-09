#include "IRGenVisitor.h"

IRGenerator(CFG *cfg_) : cfg(cfg_)
{
	BasicBlock *current_bb = new BasicBlock(cfg, "entry");
	cfg->current_bb = current_bb;
	cfg->add_bb(current_bb);
}

antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) 
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
	cfg->current_bb->add_IRInstr(IRInstr::ret, INT, {});
	return 0;
}

antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) 
{
	// cout<<"visitDeclaration\n";
	std::string varName = ctx->VAR()->getText();
	string offset = to_string(cfg->get_var_index(varName)) + "(%rbp)";
	Type type = cfg->get_var_type(varName);
	if (ctx->expr())
	{
		// std::string rhs = any_cast<std::string>(visit(ctx->expr()));
		// string rhsOffset =  to_string(cfg->get_var_index(rhs)) + "(%rbp)";
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

antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) 
{
	// cout<<"visitAssignment\n";
	std::string varName = ctx->VAR()->getText();
	string offset = to_string(cfg->get_var_index(varName)) + "(%rbp)";
	Type type = cfg->get_var_type(varName);
	// std::string rhs = any_cast<std::string>(visit(ctx->expr()));
	// string rhsOffset =  to_string(cfg->get_var_index(rhs)) + "(%rbp)";
	antlrcpp::Any value = visit(ctx->expr());
	// cout<<" varName" <<varName<<rhs <<"rhs "<< rhs<< endl ;
	cfg->current_bb->add_IRInstr(IRInstr::copy, type, {offset});
	return value;
}

antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) 
{
	// return ctx->VAR()->getText();
	std::string varName = ctx->VAR()->getText();
	string offset = to_string(cfg->get_var_index(varName)) + "(%rbp)";
	Type type = cfg->get_var_type(varName);
	cfg->current_bb->add_IRInstr(IRInstr::ldconst, type, {offset});
	return 0;
}

antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) 
{
	// std::string temp = cfg->create_new_tempvar(INT);
	// string offset =  to_string(cfg->get_var_index(temp))+ "(%rbp)";
	std::string value = "$" + ctx->CONST()->getText();
	cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {value});
	return 0;
}

antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) 
{
	// cout<<"visitAddSub\n";
	visit(ctx->expr(0));
	cfg->nextFreeSymbolIndex -= 4;
	string leftOffset = to_string(cfg->nextFreeSymbolIndex) + "(%rbp)";
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
	visit(ctx->expr(1));
	cfg->nextFreeSymbolIndex -= 4;
	string rightOffset = to_string(cfg->nextFreeSymbolIndex) + "(%rbp)";
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});

	std::string op = ctx->OP->getText();
	if (op == "+")
		cfg->current_bb->add_IRInstr(IRInstr::add, INT, {leftOffset, rightOffset});
	else
		cfg->current_bb->add_IRInstr(IRInstr::sub, INT, {leftOffset, rightOffset});

	return 0;
}

antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) 
{
	// cout<<"visitMulDiv\n";
	visit(ctx->expr(0));
	cfg->nextFreeSymbolIndex -= 4;
	string leftOffset = to_string(cfg->nextFreeSymbolIndex) + "(%rbp)";
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
	visit(ctx->expr(1));
	cfg->nextFreeSymbolIndex -= 4;
	string rightOffset = to_string(cfg->nextFreeSymbolIndex) + "(%rbp)";
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

antlrcpp::Any visitParExpr(ifccParser::ParExprContext *ctx) 
{
	// cout<<"visitParExpr\n";
	return visit(ctx->expr());
}

antlrcpp::Any visitNegateExpr(ifccParser::NegateExprContext *ctx) 
{
	// cout<<"visitNegateExpr\n";
	visit(ctx->expr());
	cfg->current_bb->add_IRInstr(IRInstr::neg, INT, {});
	return 0;
}

antlrcpp::Any visitNotExpr(ifccParser::NotExprContext *ctx) 
{
	visit(ctx->expr());
	cfg->current_bb->add_IRInstr(IRInstr::cmp_eq, INT, {});
	return 0;
}

antlrcpp::Any visitCmpExpr(ifccParser::CmpExprContext *ctx) 
{
	visit(ctx->expr(0));
	cfg->nextFreeSymbolIndex -= 4;
	string leftOffset = to_string(cfg->nextFreeSymbolIndex) + "(%rbp)";
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
	visit(ctx->expr(1));
	cfg->nextFreeSymbolIndex -= 4;
	string rightOffset = to_string(cfg->nextFreeSymbolIndex) + "(%rbp)";

	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
	cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {leftOffset});

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

antlrcpp::Any visitCharConstExpr(ifccParser::CharConstExprContext *ctx) 
{

	std::string text = ctx->CHAR()->getText(); // exemple : 'A'
	char c = text[1];						   // le caractère réel entre les apostrophes
	string asciiValue = " $" + to_string(static_cast<int>(c));
	cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {asciiValue});
	return 0;
}

antlrcpp::Any visitBitwiseAndExpr(ifccParser::BitwiseAndExprContext *ctx) 
{
	visit(ctx->expr(0));
	cfg->nextFreeSymbolIndex -= 4;
	string leftOffset = to_string(cfg->nextFreeSymbolIndex) + "(%rbp)";
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
	visit(ctx->expr(1));
	cfg->nextFreeSymbolIndex -= 4;
	string rightOffset = to_string(cfg->nextFreeSymbolIndex) + "(%rbp)";
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
	cfg->current_bb->add_IRInstr(IRInstr::bitwise_and, INT, {leftOffset, rightOffset});
	return 0;
}

antlrcpp::Any visitBitwiseOrExpr(ifccParser::BitwiseOrExprContext *ctx) 
{
	visit(ctx->expr(0));
	cfg->nextFreeSymbolIndex -= 4;
	string leftOffset = to_string(cfg->nextFreeSymbolIndex) + "(%rbp)";
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
	visit(ctx->expr(1));
	cfg->nextFreeSymbolIndex -= 4;
	string rightOffset = to_string(cfg->nextFreeSymbolIndex) + "(%rbp)";
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
	cfg->current_bb->add_IRInstr(IRInstr::bitwise_or, INT, {leftOffset, rightOffset});
	return 0;
}

antlrcpp::Any visitBitwiseXorExpr(ifccParser::BitwiseXorExprContext *ctx) 
{
	visit(ctx->expr(0));
	cfg->nextFreeSymbolIndex -= 4;
	string leftOffset = to_string(cfg->nextFreeSymbolIndex) + "(%rbp)";
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
	visit(ctx->expr(1));
	cfg->nextFreeSymbolIndex -= 4;
	string rightOffset = to_string(cfg->nextFreeSymbolIndex) + "(%rbp)";
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

	// if (truc = true ) : jump vers le if bloc sinon vers le else bloc
	//  cfg->current_bb->test_var_name = any_cast<std::string>(visit(ctx->expr()));
	//  string offset =  to_string(cfg->get_var_index(cfg->current_bb->test_var_name))+ "(%rbp)";
	visit(ctx->expr());
	int bbs_size = cfg->bbs.size();

	std::string if_label = "label" + to_string(bbs_size);
	BasicBlock *true_exit_bb = new BasicBlock(cfg, if_label);
	BasicBlock *previous_bb = cfg->current_bb;
	cfg->current_bb->exit_true = true_exit_bb;
	cfg->current_bb = true_exit_bb;
	cfg->add_bb(true_exit_bb);

	if (ctx->block(1))
	{
		bbs_size = cfg->bbs.size();
		string else_label = "label" + to_string(bbs_size);
		BasicBlock *false_exit_bb = new BasicBlock(cfg, else_label);
		previous_bb->exit_false = false_exit_bb;
		cfg->add_bb(false_exit_bb);
	}
	else
	{
		previous_bb->exit_false = nullptr;
	}
	bbs_size = cfg->bbs.size();
	string next_label = "label" + to_string(bbs_size);
	BasicBlock *next_bb = new BasicBlock(cfg, next_label);
	cfg->add_bb(next_bb);

	previous_bb->exit_true->exit = next_bb;
	if (previous_bb->exit_false)
	{
		previous_bb->exit_false->exit = next_bb;
	}
	next_bb->exit = previous_bb->exit;

	visit(ctx->block(0));
	if (previous_bb->exit_false)
	{
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
	if (previous_bb->exit_false)
	{
		else_or_next_label = previous_bb->exit_false->label;
	}
	else
	{
		else_or_next_label = next_bb->label;
	}

	previous_bb->add_IRInstr(IRInstr::cond_jump, INT, {if_label, else_or_next_label});

	return 0;
}

antlrcpp::Any visitFunctionCall(ifccParser::FunctionCallContext *ctx) 
{
	std::string funcName = ctx->VAR()->getText();

	if (funcName == "putchar")
	{
		std::string arg = std::any_cast<std::string>(visit(ctx->expr()));
		cfg->current_bb->add_IRInstr(IRInstr::call, INT, {"putchar", arg});
		return ""; // putchar renvoie un int, mais ici on ignore sa valeur
	}
	else if (funcName == "getchar")
	{
		std::string dst = cfg->create_new_tempvar(INT);
		cfg->current_bb->add_IRInstr(IRInstr::call, INT, {"getchar", dst});
		return dst; // on retourne le nom de la variable temporaire où est stocké le résultat
	}

	// pour d'autres fonctions plus tard...
	return 0;
}

antlrcpp::Any visitFunctionDef(ifccParser::FunctionDefContext* ctx) {
	std::string functionName = ctx->VAR()->getText();

	CFG* currentCFG = new CFG(functionName);
	cfgMap[functionName] = currentCFG;

	// cfg->current_bb->add_IRInstr(IRInstr::call, INT, {funcName});
	// return 0;
	// std::string funcName = ctx->VAR()->getText();
	// cfg->current_bb->add_IRInstr(IRInstr::call, INT, {funcName});
	return 0;
}