
#pragma once
#include "IRGenerator.h"

antlrcpp::Any IRGenerator::visitReturn_stmt(ifccParser::Return_stmtContext *ctx)
{
	visit(ctx->expr());

	// Utilisation du stack_allocation déjà calculé
	cfg->current_bb->add_IRInstr(IRInstr::ret, INT, {to_string(cfg->stack_allocation)});

	return 0;
}

antlrcpp::Any IRGenerator::visitDeclaration(ifccParser::DeclarationContext *ctx)
{

	std::string varName = ctx->VAR()->getText();
	string offset = to_string(cfg->get_var_index(varName));
	// cout<<"# Declaration : "<< endl;
	Type type = cfg->get_var_type(varName);
	if (ctx->expr())
	{

		visit(ctx->expr());
		cfg->current_bb->add_IRInstr(IRInstr::copy, type, {offset});
	}
	// else
	// {
	// 	cfg->current_bb->add_IRInstr(IRInstr::ldvar, type, {"0"});
	// }

	return 0;
}

antlrcpp::Any IRGenerator::visitAssignment(ifccParser::AssignmentContext *ctx)
{
	std::string varName = ctx->VAR()->getText();
	string offset = to_string(cfg->get_var_index(varName));
	Type type = cfg->get_var_type(varName);

	antlrcpp::Any value = visit(ctx->expr());

	cfg->current_bb->add_IRInstr(IRInstr::copy, type, {offset});
	return value;
}

antlrcpp::Any IRGenerator::visitVarExpr(ifccParser::VarExprContext *ctx)
{
	std::string varName = ctx->VAR()->getText();
	string offset = to_string(cfg->get_var_index(varName));
	Type type = cfg->get_var_type(varName);
	cfg->current_bb->add_IRInstr(IRInstr::ldvar, type, {offset});
	return 0;
}

antlrcpp::Any IRGenerator::visitConstExpr(ifccParser::ConstExprContext *ctx)
{
	std::string value = ctx->CONST()->getText();
	cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {value});
	return 0;
}

antlrcpp::Any IRGenerator::visitAddSub(ifccParser::AddSubContext *ctx)
{

	visit(ctx->expr(0));
	int nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset;
	cfg->functions[cfg->currentFunction].stackOffset -= 4;
	string leftOffset = to_string(nextFreeSymbolIndex);
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
	visit(ctx->expr(1));
	nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset;
	cfg->functions[cfg->currentFunction].stackOffset -= 4;
	string rightOffset = to_string(nextFreeSymbolIndex);
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});

	std::string op = ctx->OP->getText();
	if (op == "+")
		cfg->current_bb->add_IRInstr(IRInstr::add, INT, {leftOffset, rightOffset});
	else
		cfg->current_bb->add_IRInstr(IRInstr::sub, INT, {leftOffset, rightOffset});

	return 0;
}

antlrcpp::Any IRGenerator::visitMulDiv(ifccParser::MulDivContext *ctx)
{
	// cout<<"visitMulDiv\n";
	visit(ctx->expr(0));
	int nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset;
	cfg->functions[cfg->currentFunction].stackOffset -= 4;
	string leftOffset = to_string(nextFreeSymbolIndex);
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
	visit(ctx->expr(1));
	nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset;
	cfg->functions[cfg->currentFunction].stackOffset -= 4;
	string rightOffset = to_string(nextFreeSymbolIndex);
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

antlrcpp::Any IRGenerator::visitParExpr(ifccParser::ParExprContext *ctx)
{
	return visit(ctx->expr());
}

antlrcpp::Any IRGenerator::visitNegateExpr(ifccParser::NegateExprContext *ctx)
{
	visit(ctx->expr());
	cfg->current_bb->add_IRInstr(IRInstr::neg, INT, {});
	return 0;
}

antlrcpp::Any IRGenerator::visitNotExpr(ifccParser::NotExprContext *ctx)
{
	visit(ctx->expr());
	cfg->current_bb->add_IRInstr(IRInstr::cmp_eq, INT, {});
	return 0;
}

antlrcpp::Any IRGenerator::visitCmpExpr(ifccParser::CmpExprContext *ctx)
{
	visit(ctx->expr(0));
	int nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset;
	cfg->functions[cfg->currentFunction].stackOffset -= 4;
	string leftOffset = to_string(nextFreeSymbolIndex);
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
	visit(ctx->expr(1));
	nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset;
	cfg->functions[cfg->currentFunction].stackOffset -= 4;
	string rightOffset = to_string(nextFreeSymbolIndex);

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

antlrcpp::Any IRGenerator::visitCharConstExpr(ifccParser::CharConstExprContext *ctx)
{

	std::string text = ctx->CHAR()->getText(); // exemple : 'A'
	char c = text[1];						   // le caractère réel entre les apostrophes
	string asciiValue = to_string(static_cast<int>(c));
	cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {asciiValue});
	return 0;
}

antlrcpp::Any IRGenerator::visitBitwiseAndExpr(ifccParser::BitwiseAndExprContext *ctx)
{
	visit(ctx->expr(0));
	int nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset;
	cfg->functions[cfg->currentFunction].stackOffset -= 4;
	string leftOffset = to_string(nextFreeSymbolIndex);
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
	visit(ctx->expr(1));
	nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset;
	cfg->functions[cfg->currentFunction].stackOffset -= 4;
	string rightOffset = to_string(nextFreeSymbolIndex);
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
	cfg->current_bb->add_IRInstr(IRInstr::bitwise_and, INT, {leftOffset, rightOffset});
	return 0;
}

antlrcpp::Any IRGenerator::visitBitwiseOrExpr(ifccParser::BitwiseOrExprContext *ctx)
{
	visit(ctx->expr(0));
	int nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset;
	cfg->functions[cfg->currentFunction].stackOffset -= 4;
	string leftOffset = to_string(nextFreeSymbolIndex);
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
	visit(ctx->expr(1));
	nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset;
	cfg->functions[cfg->currentFunction].stackOffset -= 4;
	string rightOffset = to_string(nextFreeSymbolIndex);
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
	cfg->current_bb->add_IRInstr(IRInstr::bitwise_or, INT, {leftOffset, rightOffset});
	return 0;
}

antlrcpp::Any IRGenerator::visitBitwiseXorExpr(ifccParser::BitwiseXorExprContext *ctx)
{
	visit(ctx->expr(0));
	int nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset;
	cfg->functions[cfg->currentFunction].stackOffset -= 4;
	string leftOffset = to_string(nextFreeSymbolIndex);
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
	visit(ctx->expr(1));
	nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset;
	cfg->functions[cfg->currentFunction].stackOffset -= 4;
	string rightOffset = to_string(nextFreeSymbolIndex);
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
	cfg->current_bb->add_IRInstr(IRInstr::bitwise_xor, INT, {leftOffset, rightOffset});
	return 0;
}

antlrcpp::Any IRGenerator::visitBlock(ifccParser::BlockContext *ctx)
{
	// BasicBlock *current_bb = new BasicBlock(cfg, "label");
	// current_bb->parent = cfg->current_bloc_index;
	// cfg->add_bb(current_bb);
	// int parent_index = cfg->current_bloc_index;

	cfg->last_ST_index += 1;
	int parentST_index = cfg->currentST_index;
	cfg->currentST_index = cfg->last_ST_index;
	// cout<<"currentST_index : "<<cfg->currentST_index<<endl;
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

antlrcpp::Any IRGenerator::visitIf_stmt(ifccParser::If_stmtContext *ctx)
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

antlrcpp::Any IRGenerator::visitWhile_stmt(ifccParser::While_stmtContext *ctx)
{

	int bbs_size = cfg->bbs.size();
	std::string condition_bb_label = "label" + to_string(bbs_size);
	BasicBlock *condition_bb = new BasicBlock(cfg, condition_bb_label);
	cfg->add_bb(condition_bb);
	bbs_size = cfg->bbs.size();
	std::string bb_true__label = "label" + to_string(bbs_size);
	BasicBlock *bb_true = new BasicBlock(cfg, bb_true__label);
	cfg->add_bb(bb_true);
	bbs_size = cfg->bbs.size();
	std::string bb_false_label = "label" + to_string(bbs_size);
	BasicBlock *bb_false = new BasicBlock(cfg, bb_false_label);
	cfg->add_bb(bb_false);
	condition_bb->exit_true = bb_true;
	condition_bb->exit_false = bb_false;
	bb_false->exit = cfg->current_bb->exit;
	bb_true->exit = condition_bb;
	cfg->current_bb->exit = condition_bb;
	cfg->current_bb->add_IRInstr(IRInstr::jump, INT, {condition_bb_label});
	cfg->current_bb = condition_bb;
	visit(ctx->expr());
	cfg->current_bb->add_IRInstr(IRInstr::cond_jump, INT, {bb_true__label, bb_false_label});

	cfg->current_bb = bb_true;
	visit(ctx->block());
	cfg->current_bb = bb_false;

	return 0;
}

antlrcpp::Any IRGenerator::visitFunctionCall(ifccParser::FunctionCallContext *ctx)
{
	// std::string funcName = ctx->VAR()->getText();

	// if (funcName == "putchar")
	// {
	// 	std::string arg = std::any_cast<std::string>(visit(ctx->expr()));
	// 	cfg->current_bb->add_IRInstr(IRInstr::call, INT, {"putchar", arg});
	// 	return ""; // putchar renvoie un int, mais ici on ignore sa valeur
	// }
	// else if (funcName == "getchar")
	// {
	// 	std::string dst = cfg->create_new_tempvar(INT);
	// 	cfg->current_bb->add_IRInstr(IRInstr::call, INT, {"getchar", dst});
	// 	return dst; // on retourne le nom de la variable temporaire où est stocké le résultat
	// }

	std::string funcName = ctx->VAR()->getText();

	// Si getchar : pas d'argument à passer
	if (funcName == "getchar")
	{
		int offset = cfg->functions[cfg->currentFunction].stackOffset;
		//string resOffset = to_string(offset);
		//cfg->functions[cfg->currentFunction].stackOffset -= 4;

		//cfg->current_bb->add_IRInstr(IRInstr::call, INT, {funcName, resOffset});
		cfg->current_bb->add_IRInstr(IRInstr::call, INT, {funcName});
		return 0;
	}
	else if (funcName == "putchar")
	{
		visit(ctx->expr(0)); // Place l'argument dans %eax

		int offset = cfg->functions[cfg->currentFunction].stackOffset;
		string resOffset = to_string(offset);
		cfg->functions[cfg->currentFunction].stackOffset -= 4;
		cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {resOffset}); // Sauvegarde %eax
		cfg->current_bb->add_IRInstr(IRInstr::call, INT, {"putchar", resOffset});
		return 0;
	}
	else
	{
		int i = 0;
		auto it = cfg->functions[funcName].symbolTable[0]->table.begin();
		while (ctx->expr(i))
		{ // Check if parameter_list exists
			// Symbol s = it->second;
			// int offset = s.symbolOffset;
			// Type type = s.symbolType;
			visit(ctx->expr(i));
			cfg->current_bb->add_IRInstr(IRInstr::assign_param, INT, {to_string(i)});
			// cfg->current_bb->add_IRInstr(IRInstr::copy, type, {to_string(offset)});
			++i;
			++it;
		}
		// if(cfg->functions[funcName].symbolTable.size() > i){
		// 	//Chnger Symbol Table Visitor , ça doit être détecté comme une erreur
		// }
		cfg->current_bb->add_IRInstr(IRInstr::call, INT, {funcName});
	}
	return 0;
}

antlrcpp::Any IRGenerator::visitFunctionDef(ifccParser::FunctionDefContext *ctx)
{
	std::string funcName = ctx->VAR()->getText();

	BasicBlock *function_bb = new BasicBlock(cfg, funcName);
	cfg->currentFunction = funcName;
	cfg->add_bb(function_bb);
	cfg->current_bb = function_bb;

	SymbolTable *symbolTable = cfg->functions[funcName].symbolTable.at(0);

	if (symbolTable != nullptr)
	{
		auto it = symbolTable->table.begin();
		int i = 0;
		for (; it != symbolTable->table.end(); ++it, ++i)
		{
			cfg->current_bb->add_IRInstr(IRInstr::load_param_from_reg, INT, {to_string(it->second.symbolOffset), to_string(i)});
		}
	}

	cfg->currentST_index = 0;
	cfg->last_ST_index = 0;

	int total = -cfg->functions[funcName].stackOffset;

	// Prévoir une grosse marge pour les temporaires (genre 20 slots de 4 bytes = 80 bytes)
	int nb_max_temp = 20;
	total += nb_max_temp * 4;

	// Minimum obligatoire
	if (total < 32)
		total = 32;

	// Alignement sur 16 bytes (obligatoire ARM)
	if (total % 16 != 0)
		total += (16 - (total % 16));

	cfg->stack_allocation = total;

	// visit du code de la fonction
	visit(ctx->block());

	// Ajout du prologue en tête
	function_bb->add_IRInstrAtTop(IRInstr::prologue, INT, {to_string(cfg->stack_allocation)});

	return 0;
}



antlrcpp::Any IRGenerator::visitMainFunction(ifccParser::MainFunctionContext *ctx)
{
	std::string funcName = "main";

	BasicBlock *function_bb = new BasicBlock(cfg, funcName);
	cfg->currentFunction = funcName;
	cfg->add_bb(function_bb);
	cfg->current_bb = function_bb;

	SymbolTable *symbolTable = cfg->functions[funcName].symbolTable.at(0);

	// if (symbolTable != nullptr)
	// {
	// 	auto it = symbolTable->table.begin();
	// 	int i = 0;
	// 	for (; it != symbolTable->table.end(); ++it, ++i)
	// 	{
	// 		cfg->current_bb->add_IRInstr(IRInstr::load_param_from_reg, INT, {to_string(it->second.symbolOffset), to_string(i)});
	// 	}
	// }

	cfg->currentST_index = 0;
	cfg->last_ST_index = 0;

	int total = -cfg->functions[funcName].stackOffset;

	// Prévoir une grosse marge pour les temporaires (genre 20 slots de 4 bytes = 80 bytes)
	int nb_max_temp = 20;
	total += nb_max_temp * 4;

	// Minimum obligatoire
	if (total < 32)
		total = 32;

	// Alignement sur 16 bytes (obligatoire ARM)
	if (total % 16 != 0)
		total += (16 - (total % 16));

	cfg->stack_allocation = total;

	// visit du code de la fonction
	visit(ctx->block());

	// Ajout du prologue en tête
	function_bb->add_IRInstrAtTop(IRInstr::prologue, INT, {to_string(cfg->stack_allocation)});

	return 0;
}
