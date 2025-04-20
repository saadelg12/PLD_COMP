#include "IRGenerator.h"

// Visite d'une instruction de retour
antlrcpp::Any IRGenerator::visitReturn_stmt(ifccParser::Return_stmtContext *ctx)
{
	visit(ctx->expr()); // Visite l'expression de retour
	Type type = cfg->functions[cfg->currentFunction].returnType; // Récupère le type de retour de la fonction
	if(type != lastExprType) // Si le type de l'expression ne correspond pas au type de retour attendu
	{
		if(type == INT) cfg->current_bb->add_IRInstr(IRInstr::double_to_int, type, {to_string(cfg->stack_allocation)}); // Conversion double -> int
		else cfg->current_bb->add_IRInstr(IRInstr::int_to_double, type, {to_string(cfg->stack_allocation)}); // Conversion int -> double
	}
	// Ajoute une instruction de retour en utilisant l'allocation de pile calculée
	cfg->current_bb->add_IRInstr(IRInstr::ret, lastExprType, {to_string(cfg->stack_allocation)});

	return 0;
}

// Visite d'une déclaration de variable
antlrcpp::Any IRGenerator::visitDeclaration(ifccParser::DeclarationContext *ctx)
{
	std::string varName = ctx->ID()->getText(); // Récupère le nom de la variable
	string offset = to_string(cfg->get_var_index(varName)); // Récupère l'offset de la variable
	Type type = cfg->get_var_type(varName); // Récupère le type de la variable
	if (ctx->expr()) // Si une expression est associée à la déclaration
	{
		visit(ctx->expr()); // Visite l'expression
		if(lastExprType == type)cfg->current_bb->add_IRInstr(IRInstr::copy, type, {offset}); // Copie directe si les types correspondent
		else{
			if (type == INT){
				cfg->current_bb->add_IRInstr(IRInstr::double_to_int, type, {offset}); // Conversion double -> int
			}
			else if (type == DOUBLE){
				cfg->current_bb->add_IRInstr(IRInstr::int_to_double, type, {offset}); // Conversion int -> double
			}
		}
	}
	lastExprType = type; // Met à jour le dernier type d'expression
	return 0;
}

// Visite d'une affectation
antlrcpp::Any IRGenerator::visitAssignment(ifccParser::AssignmentContext *ctx)
{
	std::string varName = ctx->ID()->getText(); // Récupère le nom de la variable
	string offset = to_string(cfg->get_var_index(varName)); // Récupère l'offset de la variable
	Type type = cfg->get_var_type(varName); // Récupère le type de la variable

	antlrcpp::Any value = visit(ctx->expr()); // Visite l'expression associée à l'affectation

	if(type != lastExprType) // Si le type de la variable ne correspond pas au type de l'expression
	{
		if(type == INT) cfg->current_bb->add_IRInstr(IRInstr::double_to_int, type, {offset}); // Conversion double -> int
		else cfg->current_bb->add_IRInstr(IRInstr::int_to_double, type, {offset}); // Conversion int -> double
	}

	cfg->current_bb->add_IRInstr(IRInstr::copy, type, {offset}); // Ajoute une instruction de copie
	lastExprType = type; // Met à jour le dernier type d'expression
	return value;
}

// Visite d'une expression contenant un identifiant
antlrcpp::Any IRGenerator::visitIdExpr(ifccParser::IdExprContext *ctx)
{
	std::string varName = ctx->ID()->getText(); // Récupère le nom de l'identifiant
	string offset = to_string(cfg->get_var_index(varName)); // Récupère l'offset de l'identifiant
	lastExprType = cfg->get_var_type(varName); // Met à jour le dernier type d'expression
	cfg->current_bb->add_IRInstr(IRInstr::ldvar, lastExprType, {offset}); // Ajoute une instruction pour charger la variable
	return 0;
}

// Visite d'une expression constante
antlrcpp::Any IRGenerator::visitConstExpr(ifccParser::ConstExprContext *ctx)
{
	std::string text = ctx->CONST()->getText(); // Récupère la valeur de la constante
	lastExprType = (text.find('.') != std::string::npos) ? DOUBLE : INT; // Détermine le type de la constante (int ou double)

	std::string value;

	if (text.find('.') != std::string::npos) { // Si la constante est un double
		std::string label;
		if (cfg->double_constants.count(text) == 0) { // Génère une étiquette unique pour la constante si elle n'existe pas encore
			label = "LC" + std::to_string(cfg->double_constant_counter++);
			cfg->double_constants[text] = label;
		} else {
			label = cfg->double_constants[text]; // Récupère l'étiquette existante
		}
		value = label; // Utilise l'étiquette pour l'accès mémoire
	} else {
		lastExprType = INT; // La constante est un entier
		value = text; // Utilise directement la valeur
	}

	cfg->current_bb->add_IRInstr(IRInstr::ldconst, lastExprType, {value}); // Ajoute une instruction pour charger la constante
	return 0;
}

// Visite d'une addition ou soustraction
antlrcpp::Any IRGenerator::visitAddSub(ifccParser::AddSubContext *ctx)
{
	visit(ctx->expr(0)); // Visite le premier opérande
	Type leftType = lastExprType; // Récupère le type du premier opérande
	int nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset; // Récupère l'index libre suivant dans la pile
	cfg->functions[cfg->currentFunction].stackOffset -= getTypeSize(leftType); // Réserve de l'espace pour le premier opérande
	string leftOffset = to_string(nextFreeSymbolIndex); // Récupère l'offset du premier opérande
	cfg->current_bb->add_IRInstr(IRInstr::copy, leftType, {leftOffset}); // Ajoute une instruction pour copier le premier opérande
	visit(ctx->expr(1)); // Visite le second opérande
	Type rightType = lastExprType; // Récupère le type du second opérande
	nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset; // Récupère l'index libre suivant dans la pile
	cfg->functions[cfg->currentFunction].stackOffset -= getTypeSize(rightType); // Réserve de l'espace pour le second opérande
	string rightOffset = to_string(nextFreeSymbolIndex); // Récupère l'offset du second opérande
	cfg->current_bb->add_IRInstr(IRInstr::copy, rightType, {rightOffset}); // Ajoute une instruction pour copier le second opérande

	if (leftType == DOUBLE || rightType == DOUBLE) { // Si l'un des opérandes est un double
		lastExprType = DOUBLE; // Le résultat sera un double
		
		if (leftType == INT) { // Conversion du premier opérande en double si nécessaire
			leftOffset = to_string(cfg->functions[cfg->currentFunction].stackOffset);
			cfg->functions[cfg->currentFunction].stackOffset -= getTypeSize(lastExprType);
			cfg->current_bb->add_IRInstr(IRInstr::int_to_double, DOUBLE, {leftOffset});
		}
		if (rightType == INT) { // Conversion du second opérande en double si nécessaire
			rightOffset = to_string(cfg->functions[cfg->currentFunction].stackOffset);
			cfg->functions[cfg->currentFunction].stackOffset -= getTypeSize(lastExprType);
			cfg->current_bb->add_IRInstr(IRInstr::int_to_double, DOUBLE, {rightOffset});
		}
	} else {
		lastExprType = INT; // Sinon, le résultat sera un entier
	}

	std::string op = ctx->OP->getText(); // Récupère l'opérateur (+ ou -)
	if (op == "+")
		cfg->current_bb->add_IRInstr(IRInstr::add, lastExprType, {leftOffset, rightOffset}); // Ajoute une instruction d'addition
	else
		cfg->current_bb->add_IRInstr(IRInstr::sub, lastExprType, {leftOffset, rightOffset}); // Ajoute une instruction de soustraction

	return 0;
}

// Visite d'une multiplication ou division
antlrcpp::Any IRGenerator::visitMulDiv(ifccParser::MulDivContext *ctx)
{
	visit(ctx->expr(0)); // Visite le premier opérande
	Type leftType = lastExprType; // Récupère le type du premier opérande
	int nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset; // Récupère l'index libre suivant dans la pile
	cfg->functions[cfg->currentFunction].stackOffset -= getTypeSize(leftType); // Réserve de l'espace pour le premier opérande
	string leftOffset = to_string(nextFreeSymbolIndex); // Récupère l'offset du premier opérande
	cfg->current_bb->add_IRInstr(IRInstr::copy, leftType, {leftOffset}); // Ajoute une instruction pour copier le premier opérande
	visit(ctx->expr(1)); // Visite le second opérande
	Type rightType = lastExprType; // Récupère le type du second opérande
	nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset; // Récupère l'index libre suivant dans la pile
	cfg->functions[cfg->currentFunction].stackOffset -= getTypeSize(rightType); // Réserve de l'espace pour le second opérande
	string rightOffset = to_string(nextFreeSymbolIndex); // Récupère l'offset du second opérande
	cfg->current_bb->add_IRInstr(IRInstr::copy, rightType, {rightOffset}); // Ajoute une instruction pour copier le second opérande

	if (leftType == DOUBLE || rightType == DOUBLE) { // Si l'un des opérandes est un double
		lastExprType = DOUBLE; // Le résultat sera un double
		
		if (leftType == INT) { // Conversion du premier opérande en double si nécessaire
			leftOffset = to_string(cfg->functions[cfg->currentFunction].stackOffset);
			cfg->functions[cfg->currentFunction].stackOffset -= getTypeSize(lastExprType);
			cfg->current_bb->add_IRInstr(IRInstr::int_to_double, DOUBLE, {leftOffset});
		}
		if (rightType == INT) { // Conversion du second opérande en double si nécessaire
			rightOffset = to_string(cfg->functions[cfg->currentFunction].stackOffset);
			cfg->functions[cfg->currentFunction].stackOffset -= getTypeSize(lastExprType);
			cfg->current_bb->add_IRInstr(IRInstr::int_to_double, DOUBLE, {rightOffset});
		}
	} else {
		lastExprType = INT; // Sinon, le résultat sera un entier
	}

	std::string op = ctx->OP->getText(); // Récupère l'opérateur (* ou / ou %)
	if (op == "*")
	{
		cfg->current_bb->add_IRInstr(IRInstr::mul, lastExprType, {leftOffset, rightOffset}); // Ajoute une instruction de multiplication
	}
	else if (op == "/")
	{
		cfg->current_bb->add_IRInstr(IRInstr::div, lastExprType, {leftOffset, rightOffset}); // Ajoute une instruction de division
	}
	else if (op == "%")
	{
		cfg->current_bb->add_IRInstr(IRInstr::mod, INT, {leftOffset, rightOffset}); // Ajoute une instruction de modulo
	}
	return 0;
}

// Visite d'une expression entre parenthèses
antlrcpp::Any IRGenerator::visitParExpr(ifccParser::ParExprContext *ctx)
{
	return visit(ctx->expr()); // Visite l'expression entre parenthèses
}

// Visite d'une expression de négation
antlrcpp::Any IRGenerator::visitNegateExpr(ifccParser::NegateExprContext *ctx)
{
	visit(ctx->expr()); // Visite l'expression à négativer
	cfg->current_bb->add_IRInstr(IRInstr::neg, INT, {}); // Ajoute une instruction de négation
	return 0;
}

// Visite d'une expression de négation logique
antlrcpp::Any IRGenerator::visitNotExpr(ifccParser::NotExprContext *ctx)
{
	visit(ctx->expr()); // Visite l'expression à négativer
	cfg->current_bb->add_IRInstr(IRInstr::cmp_eq, INT, {}); // Ajoute une instruction de comparaison pour vérifier l'égalité à zéro
	return 0;
}

// Visite d'une expression de comparaison
antlrcpp::Any IRGenerator::visitCmpExpr(ifccParser::CmpExprContext *ctx)
{
	visit(ctx->expr(0)); // Visite le premier opérande
	Type leftType = lastExprType; // Récupère le type du premier opérande
	int nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset; // Récupère l'index libre suivant dans la pile
	cfg->functions[cfg->currentFunction].stackOffset -= getTypeSize(leftType); // Réserve de l'espace pour le premier opérande
	string leftOffset = to_string(nextFreeSymbolIndex); // Récupère l'offset du premier opérande
	cfg->current_bb->add_IRInstr(IRInstr::copy, leftType, {leftOffset}); // Ajoute une instruction pour copier le premier opérande
	visit(ctx->expr(1)); // Visite le second opérande
	Type rightType = lastExprType; // Récupère le type du second opérande
	nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset; 	// Récupère l'index libre suivant dans la pile
	cfg->functions[cfg->currentFunction].stackOffset -= getTypeSize(rightType); // Réserve de l'espace pour le second opérande
	string rightOffset = to_string(nextFreeSymbolIndex); // Récupère l'offset du second opérande
	cfg->current_bb->add_IRInstr(IRInstr::copy, rightType, {rightOffset}); // Ajoute une instruction pour copier le second opérande

	if (leftType == DOUBLE || rightType == DOUBLE) { // Si l'un des opérandes est un double
        lastExprType = DOUBLE; 
        if (leftType == INT) 
            cfg->current_bb->add_IRInstr(IRInstr::int_to_double, DOUBLE, {leftOffset}); 
        if (rightType == INT)
            cfg->current_bb->add_IRInstr(IRInstr::int_to_double, DOUBLE, {rightOffset});
    } else {
        lastExprType = INT;
    }
	// Ajoute une instruction de comparaison
	cfg->current_bb->add_IRInstr(IRInstr::ldvar, lastExprType, {leftOffset});

	std::string op = ctx->getText(); // Récupère l'opérateur de comparaison
	std::string setInstr;

	// Détermine l'instruction de comparaison à utiliser en fonction de l'opérateur
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

	cfg->current_bb->add_IRInstr(IRInstr::cmp_expr, lastExprType, {rightOffset, setInstr});
	lastExprType = INT;
	return 0;
}

// Visite d'une expression de caractère
antlrcpp::Any IRGenerator::visitCharConstExpr(ifccParser::CharConstExprContext *ctx)
{

	std::string text = ctx->CHAR()->getText(); // exemple : 'A'
	char c = text[1];						   // le caractère réel entre les apostrophes
	string asciiValue = to_string(static_cast<int>(c));
	cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {asciiValue});
	lastExprType = INT;
	return 0;
}

// Visite d'une expression de bitwise AND
antlrcpp::Any IRGenerator::visitBitwiseAndExpr(ifccParser::BitwiseAndExprContext *ctx)
{
	visit(ctx->expr(0));
	int nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset; // Récupère l'index libre suivant dans la pile
	cfg->functions[cfg->currentFunction].stackOffset -= 4; // Réserve de l'espace pour le premier opérande
	string leftOffset = to_string(nextFreeSymbolIndex); // Récupère l'offset du premier opérande
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
	visit(ctx->expr(1));
	nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset;  
	cfg->functions[cfg->currentFunction].stackOffset -= 4; // Réserve de l'espace pour le second opérande
	string rightOffset = to_string(nextFreeSymbolIndex); // Récupère l'offset du second opérande
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset}); // Ajoute une instruction pour copier le second opérande
	cfg->current_bb->add_IRInstr(IRInstr::bitwise_and, INT, {leftOffset, rightOffset}); // Ajoute une instruction de bitwise AND
	return 0;
}

// Visite d'une expression de bitwise OR
antlrcpp::Any IRGenerator::visitBitwiseOrExpr(ifccParser::BitwiseOrExprContext *ctx)
{
	visit(ctx->expr(0)); // Visite le premier opérande de l'expression
	int nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset; // Récupère l'index libre suivant dans la pile
	cfg->functions[cfg->currentFunction].stackOffset -= 4; // Réserve de l'espace pour le premier opérande
	string leftOffset = to_string(nextFreeSymbolIndex); // Récupère l'offset du premier opérande
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset}); // Ajoute une instruction pour copier le premier opérande
	visit(ctx->expr(1)); // Visite le second opérande de l'expression
	nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset; // Récupère l'index libre suivant dans la pile
	cfg->functions[cfg->currentFunction].stackOffset -= 4; // Réserve de l'espace pour le second opérande
	string rightOffset = to_string(nextFreeSymbolIndex); // Récupère l'offset du second opérande
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset}); // Ajoute une instruction pour copier le second opérande
	cfg->current_bb->add_IRInstr(IRInstr::bitwise_or, INT, {leftOffset, rightOffset}); // Ajoute une instruction pour effectuer l'opération bitwise OR
	return 0;  
}

// Visite d'une expression de bitwise XOR
antlrcpp::Any IRGenerator::visitBitwiseXorExpr(ifccParser::BitwiseXorExprContext *ctx)
{
	visit(ctx->expr(0)); // Visite le premier opérande de l'expression
	int nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset; // Récupère l'index libre suivant dans la pile
	cfg->functions[cfg->currentFunction].stackOffset -= 4; // Réserve de l'espace pour le premier opérande
	string leftOffset = to_string(nextFreeSymbolIndex); // Récupère l'offset du premier opérande
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset}); // Ajoute une instruction pour copier le premier opérande
	visit(ctx->expr(1)); // Visite le second opérande de l'expression
	nextFreeSymbolIndex = cfg->functions[cfg->currentFunction].stackOffset; // Récupère l'index libre suivant dans la pile
	cfg->functions[cfg->currentFunction].stackOffset -= 4; // Réserve de l'espace pour le second opérande
	string rightOffset = to_string(nextFreeSymbolIndex); // Récupère l'offset du second opérande
	cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset}); // Ajoute une instruction pour copier le second opérande
	cfg->current_bb->add_IRInstr(IRInstr::bitwise_xor, INT, {leftOffset, rightOffset}); // Ajoute une instruction pour effectuer l'opération bitwise XOR
	return 0; 
}

// Visite d'un bloc de code
antlrcpp::Any IRGenerator::visitBlock(ifccParser::BlockContext *ctx)
{
	// Incrémente l'index du dernier SymbolTable pour créer un nouveau contexte
	cfg->last_ST_index += 1;

	// Sauvegarde l'index du SymbolTable parent
	int parentST_index = cfg->currentST_index;

	// Met à jour l'index courant du SymbolTable pour le nouveau contexte
	cfg->currentST_index = cfg->last_ST_index;

	// Parcourt toutes les instructions (statements) du bloc
	for (auto stmt : ctx->stmt())
	{
		// Visite chaque instruction
		this->visit(stmt);
	}

	// Restaure l'index du SymbolTable parent après avoir traité le bloc
	cfg->currentST_index = parentST_index;

	// Si le bloc courant a un bloc de sortie (exit), ajoute une instruction de saut
	if (cfg->current_bb->exit)
	{
		cfg->current_bb->add_IRInstr(IRInstr::jump, INT, {cfg->current_bb->exit->label});
	}


	return 0;
}

antlrcpp::Any IRGenerator::visitIf_stmt(ifccParser::If_stmtContext *ctx)
{
	// Visite l'expression conditionnelle de l'instruction if
	visit(ctx->expr());
	int bbs_size = cfg->bbs.size(); // Récupère le nombre actuel de BasicBlocks

	// Création d'un BasicBlock pour le bloc "if"
	std::string if_label = "label" + to_string(bbs_size);
	BasicBlock *true_exit_bb = new BasicBlock(cfg, if_label);
	BasicBlock *previous_bb = cfg->current_bb; // Sauvegarde du BasicBlock courant
	cfg->current_bb->exit_true = true_exit_bb; // Définit le bloc "if" comme sortie vraie du bloc courant
	cfg->current_bb = true_exit_bb; // Met à jour le BasicBlock courant
	cfg->add_bb(true_exit_bb); // Ajoute le bloc "if" à la liste des BasicBlocks

	// Si un bloc "else" existe
	if (ctx->block(1))
	{
		bbs_size = cfg->bbs.size(); // Récupère le nombre actuel de BasicBlocks
		string else_label = "label" + to_string(bbs_size); // Génère un label pour le bloc "else"
		BasicBlock *false_exit_bb = new BasicBlock(cfg, else_label); // Création du BasicBlock pour le bloc "else"
		previous_bb->exit_false = false_exit_bb; // Définit le bloc "else" comme sortie fausse du bloc précédent
		cfg->add_bb(false_exit_bb); // Ajoute le bloc "else" à la liste des BasicBlocks
	}
	else
	{
		previous_bb->exit_false = nullptr; // Si pas de bloc "else", la sortie fausse est nulle
	}

	// Création d'un BasicBlock pour la suite après le "if" (et éventuellement le "else")
	bbs_size = cfg->bbs.size(); // Récupère le nombre actuel de BasicBlocks
	string next_label = "label" + to_string(bbs_size); // Génère un label pour le bloc suivant
	BasicBlock *next_bb = new BasicBlock(cfg, next_label); // Création du BasicBlock pour la suite
	cfg->add_bb(next_bb); // Ajoute le bloc suivant à la liste des BasicBlocks

	// Définit les sorties des blocs "if" et "else" vers le bloc suivant
	previous_bb->exit_true->exit = next_bb;
	if (previous_bb->exit_false)
	{
		previous_bb->exit_false->exit = next_bb;
	}
	next_bb->exit = previous_bb->exit; // Définit la sortie du bloc suivant comme celle du bloc précédent

	// Visite le bloc "if"
	visit(ctx->block(0));
	if (previous_bb->exit_false)
	{
		// Si un bloc "else" existe, visite ce bloc
		cfg->current_bb = previous_bb->exit_false;
		visit(ctx->block(1));
	}

	// Met à jour le BasicBlock courant pour qu'il soit le bloc suivant
	cfg->current_bb = next_bb;

	// Détermine le label pour le saut conditionnel (vers "else" ou "next")
	std::string else_or_next_label;
	if (previous_bb->exit_false)
	{
		else_or_next_label = previous_bb->exit_false->label; // Label du bloc "else"
	}
	else
	{
		else_or_next_label = next_bb->label; // Label du bloc suivant
	}

	// Ajoute une instruction de saut conditionnel dans le bloc précédent
	previous_bb->add_IRInstr(IRInstr::cond_jump, INT, {if_label, else_or_next_label});

	return 0; 
}

antlrcpp::Any IRGenerator::visitWhile_stmt(ifccParser::While_stmtContext *ctx)
{
	// Récupère le nombre actuel de BasicBlocks pour générer un label pour le bloc de condition
	int bbs_size = cfg->bbs.size();
	std::string condition_bb_label = "label" + to_string(bbs_size);
	BasicBlock *condition_bb = new BasicBlock(cfg, condition_bb_label); // Crée un BasicBlock pour la condition
	cfg->add_bb(condition_bb); // Ajoute le bloc de condition à la liste des BasicBlocks

	// Récupère le nombre actuel de BasicBlocks pour générer un label pour le bloc "vrai"
	bbs_size = cfg->bbs.size();
	std::string bb_true__label = "label" + to_string(bbs_size);
	BasicBlock *bb_true = new BasicBlock(cfg, bb_true__label); // Crée un BasicBlock pour le bloc "vrai"
	cfg->add_bb(bb_true); // Ajoute le bloc "vrai" à la liste des BasicBlocks

	// Récupère le nombre actuel de BasicBlocks pour générer un label pour le bloc "faux"
	bbs_size = cfg->bbs.size();
	std::string bb_false_label = "label" + to_string(bbs_size);
	BasicBlock *bb_false = new BasicBlock(cfg, bb_false_label); // Crée un BasicBlock pour le bloc "faux"
	cfg->add_bb(bb_false); // Ajoute le bloc "faux" à la liste des BasicBlocks

	// Définit les sorties du bloc de condition
	condition_bb->exit_true = bb_true; // Si la condition est vraie, on va au bloc "vrai"
	condition_bb->exit_false = bb_false; // Si la condition est fausse, on va au bloc "faux"

	// Définit la sortie du bloc "faux" comme étant la sortie du bloc courant
	bb_false->exit = cfg->current_bb->exit;

	// Définit la sortie du bloc "vrai" comme étant le bloc de condition (boucle)
	bb_true->exit = condition_bb;

	// Définit la sortie du bloc courant comme étant le bloc de condition
	cfg->current_bb->exit = condition_bb;

	// Ajoute une instruction de saut vers le bloc de condition
	cfg->current_bb->add_IRInstr(IRInstr::jump, INT, {condition_bb_label});

	// Met à jour le BasicBlock courant pour qu'il soit le bloc de condition
	cfg->current_bb = condition_bb;

	// Visite l'expression conditionnelle
	visit(ctx->expr());

	// Ajoute une instruction de saut conditionnel dans le bloc de condition
	cfg->current_bb->add_IRInstr(IRInstr::cond_jump, INT, {bb_true__label, bb_false_label});

	// Met à jour le BasicBlock courant pour qu'il soit le bloc "vrai"
	cfg->current_bb = bb_true;

	// Visite le bloc de code associé à la boucle
	visit(ctx->block());

	// Met à jour le BasicBlock courant pour qu'il soit le bloc "faux"
	cfg->current_bb = bb_false;

	return 0; 
}

antlrcpp::Any IRGenerator::visitFunctionCall(ifccParser::FunctionCallContext *ctx)
{
	// Récupère le nom de la fonction appelée
	std::string funcName = ctx->ID()->getText();

	// Cas particulier : si la fonction appelée est "getchar"
	if (funcName == "getchar")
	{
		// Récupère l'offset de la pile pour la fonction courante
		int offset = cfg->functions[cfg->currentFunction].stackOffset;

		// Génère un label unique pour l'appel à getchar
		std::string getchar_label = "read_car_" + to_string(cfg->nb_getchar++);

		// Ajoute une instruction IR pour appeler la fonction "getchar"
		cfg->current_bb->add_IRInstr(IRInstr::call, INT, {funcName, getchar_label});
		return 0; // Retourne 0 après l'appel
	}
	// Cas particulier : si la fonction appelée est "putchar"
	else if (funcName == "putchar")
	{
		// Visite l'expression passée en argument à "putchar"
		visit(ctx->expr(0)); // Place l'argument dans %eax

		// Ajoute une instruction IR pour appeler la fonction "putchar"
		cfg->current_bb->add_IRInstr(IRInstr::call, INT, {"putchar"});
		return 0; // Retourne 0 après l'appel
	}
	// Cas général : appel d'une autre fonction
	else
	{
		int i = 0; // Initialise un compteur pour les arguments
		auto it = cfg->functions[funcName].symbolTable[0]->table.begin(); // Récupère le début de la table des symboles de la fonction appelée
		Type type = cfg->functions[funcName].returnType; // Récupère le type de retour de la fonction appelée

		// Parcourt les expressions passées en arguments à la fonction
		while (ctx->expr(i))
		{
			// Visite chaque expression (argument)
			visit(ctx->expr(i));

			// Ajoute une instruction IR pour assigner l'argument au registre correspondant
			cfg->current_bb->add_IRInstr(IRInstr::assign_param, lastExprType, {to_string(i)});

			++i; // Passe à l'argument suivant
			++it; // Passe au symbole suivant dans la table des symboles
		}

		// Ajoute une instruction IR pour appeler la fonction
		cfg->current_bb->add_IRInstr(IRInstr::call, type, {funcName});
	}
	return 0; // Retourne 0 après l'appel
}

// Visite d'une définition de fonction
antlrcpp::Any IRGenerator::visitFunctionDef(ifccParser::FunctionDefContext *ctx)
{
	// Récupère le nom de la fonction définie
	std::string funcName = ctx->ID()->getText();

	// Crée un nouveau BasicBlock pour la fonction
	BasicBlock *function_bb = new BasicBlock(cfg, funcName);
	cfg->currentFunction = funcName; // Met à jour la fonction courante
	cfg->add_bb(function_bb); // Ajoute le BasicBlock de la fonction à la liste des BasicBlocks
	cfg->current_bb = function_bb; // Définit le BasicBlock courant comme celui de la fonction

	// Récupère la table des symboles associée à la fonction
	SymbolTable *symbolTable = cfg->functions[funcName].symbolTable.at(0);

	// Si la table des symboles n'est pas nulle
	if (symbolTable != nullptr)
	{
		// Parcourt les symboles de la table
		auto it = symbolTable->table.begin();
		int i = 0;
		for (; it != symbolTable->table.end(); ++it, ++i)
		{
			// Ajoute une instruction IR pour charger les paramètres depuis les registres
			cfg->current_bb->add_IRInstr(IRInstr::load_param_from_reg, INT, {to_string(it->second.symbolOffset), to_string(i)});
		}
	}

	// Initialise les indices des SymbolTables
	cfg->currentST_index = 0;
	cfg->last_ST_index = 0;

	// Calcule la taille totale de la pile pour la fonction
	int total = -cfg->functions[funcName].stackOffset;

	// Prévoit une marge pour les variables temporaires (20 slots de 4 bytes = 80 bytes)
	int nb_max_temp = 20;
	total += nb_max_temp * 4;

	// Définit une taille minimale obligatoire pour la pile
	if (total < 32)
		total = 32;

	// Aligne la taille de la pile sur 16 bytes (obligatoire pour ARM)
	if (total % 16 != 0)
		total += (16 - (total % 16));

	// Met à jour la taille d'allocation de la pile
	cfg->stack_allocation = total;

	// Visite le bloc de code de la fonction
	visit(ctx->block());

	// Ajoute une instruction de prologue en tête du BasicBlock
	function_bb->add_IRInstrAtTop(IRInstr::prologue, INT, {to_string(cfg->stack_allocation)});

	return 0; 
}


// Visite de la fonction principale (main)
antlrcpp::Any IRGenerator::visitMainFunction(ifccParser::MainFunctionContext *ctx)
{
	// Nom de la fonction principale
	std::string funcName = "main";

	// Création d'un nouveau BasicBlock pour la fonction principale
	BasicBlock *function_bb = new BasicBlock(cfg, funcName);
	cfg->currentFunction = funcName; // Mise à jour de la fonction courante
	cfg->add_bb(function_bb); // Ajout du BasicBlock à la liste des BasicBlocks
	cfg->current_bb = function_bb; // Définition du BasicBlock courant

	// Récupération de la table des symboles associée à la fonction principale
	SymbolTable *symbolTable = cfg->functions[funcName].symbolTable.at(0);

	// Code commenté pour charger les paramètres depuis les registres (non utilisé ici)
	// if (symbolTable != nullptr)
	// {
	// 	auto it = symbolTable->table.begin();
	// 	int i = 0;
	// 	for (; it != symbolTable->table.end(); ++it, ++i)
	// 	{
	// 		cfg->current_bb->add_IRInstr(IRInstr::load_param_from_reg, INT, {to_string(it->second.symbolOffset), to_string(i)});
	// 	}
	// }

	// Initialisation des indices des SymbolTables
	cfg->currentST_index = 0;
	cfg->last_ST_index = 0;

	// Calcul de la taille totale de la pile pour la fonction principale
	int total = -cfg->functions[funcName].stackOffset;

	// Prévoir une marge pour les variables temporaires (20 slots de 4 bytes = 80 bytes)
	int nb_max_temp = 20;
	total += nb_max_temp * 4;

	// Taille minimale obligatoire pour la pile
	if (total < 32)
		total = 32;

	// Alignement de la taille de la pile sur 16 bytes (obligatoire pour ARM)
	if (total % 16 != 0)
		total += (16 - (total % 16));

	// Mise à jour de la taille d'allocation de la pile
	cfg->stack_allocation = total;

	// Visite du bloc de code de la fonction principale
	visit(ctx->block());
	// Ajout du prologue en tête
	function_bb->add_IRInstrAtTop(IRInstr::prologue, INT, {to_string(cfg->stack_allocation)});

	return 0;
}
