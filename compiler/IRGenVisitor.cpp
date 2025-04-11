#include "IRGenVisitor.h"

IRGenVisitor::IRGenVisitor(CFG *cfg_) : cfg(cfg_) {
    BasicBlock *current_bb = new BasicBlock(cfg, "entry");
    cfg->current_bb = current_bb;
    cfg->add_bb(current_bb);
}

antlrcpp::Any  IRGenVisitor::visitReturn_stmt(ifccParser::Return_stmtContext *ctx)
{
    visit(ctx->expr());
    cfg->current_bb->add_IRInstr(IRInstr::ret, lastExprType, {});
    return 0;
}

antlrcpp::Any IRGenVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx)
{
    // cout<<"visitDeclaration\n";
    std::string varName = ctx->VAR()->getText();
    string offset = to_string(cfg->get_var_index(varName));
    Type type = cfg->get_var_type(varName);
    if (ctx->expr())
    {
        visit(ctx->expr());
        if(lastExprType == type)cfg->current_bb->add_IRInstr(IRInstr::copy, type, {offset});
        else{
            if (type == INT){
                cfg->current_bb->add_IRInstr(IRInstr::double_to_int, type, {offset});
            }
            else if (type == DOUBLE){
                cfg->current_bb->add_IRInstr(IRInstr::int_to_double, type, {offset});
            }
        }
        
    }
    // else
    // {
    // 	// Initialisation implicite à 0
    // 	cfg->current_bb->add_IRInstr(IRInstr::ldvar, type, {"0"});
    // }
    lastExprType = type;
    return 0;
}

antlrcpp::Any IRGenVisitor::visitAssignment(ifccParser::AssignmentContext *ctx)
{
    // cout<<"visitAssignment\n";
    std::string varName = ctx->VAR()->getText();
    string offset = to_string(cfg->get_var_index(varName));
    Type type = cfg->get_var_type(varName);
    // std::string rhs = any_cast<std::string>(visit(ctx->expr()));
    // string rhsOffset =  to_string(cfg->get_var_index(rhs)) + "(%rbp)";
    antlrcpp::Any value = visit(ctx->expr());
    // cout<<" varName" <<varName<<rhs <<"rhs "<< rhs<< endl ;
    if(type != lastExprType)
    {
        if(type == INT) cfg->current_bb->add_IRInstr(IRInstr::double_to_int, type, {offset});
        else cfg->current_bb->add_IRInstr(IRInstr::int_to_double, type, {offset});
    }
    cfg->current_bb->add_IRInstr(IRInstr::copy, type, {offset});
    lastExprType = type;
    return value;
}

antlrcpp::Any IRGenVisitor::visitVarExpr(ifccParser::VarExprContext *ctx)
{
    // return ctx->VAR()->getText();
    std::string varName = ctx->VAR()->getText();
    string offset = to_string(cfg->get_var_index(varName));
    lastExprType = cfg->get_var_type(varName);
    //cout<<"NAME : "<<varName<<"   Type :"<<lastExprType<<endl;
    cfg->current_bb->add_IRInstr(IRInstr::ldvar, lastExprType, {offset});
    return 0;
}

antlrcpp::Any IRGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx)
{
    std::string text = ctx->CONST()->getText();
    lastExprType = (text.find('.') != std::string::npos) ? DOUBLE : INT;

    std::string value;

    if (text.find('.') != std::string::npos) {

        // Génère une étiquette unique pour la constante si elle n’existe pas encore
        std::string label;
        if (cfg->double_constants.count(text) == 0) {
            label = "LC" + std::to_string(cfg->double_constant_counter++);
            cfg->double_constants[text] = label;
        } else {
            label = cfg->double_constants[text];
        }

        value = label;  // accès mémoire relatif à RIP
    } else {
        lastExprType = INT;
        value = text;
    }

    cfg->current_bb->add_IRInstr(IRInstr::ldconst, lastExprType, {value});
    return 0;
}

antlrcpp::Any IRGenVisitor::visitAddSub(ifccParser::AddSubContext *ctx)
{
    // cout<<"visitAddSub\n";
    visit(ctx->expr(0));
    Type leftType = lastExprType;
    
    string leftOffset = to_string(cfg->nextFreeSymbolIndex);
    cfg->nextFreeSymbolIndex -= getTypeSize(leftType);
    cfg->current_bb->add_IRInstr(IRInstr::copy, leftType, {leftOffset});
    
    visit(ctx->expr(1));
    Type rightType = lastExprType;
    
    string rightOffset = to_string(cfg->nextFreeSymbolIndex);
    cfg->nextFreeSymbolIndex -= getTypeSize(rightType);
    cfg->current_bb->add_IRInstr(IRInstr::copy, lastExprType, {rightOffset});

    
    if (leftType == DOUBLE || rightType == DOUBLE) {
        lastExprType = DOUBLE;
        
        if (leftType == INT) {
            
            leftOffset = to_string(cfg->nextFreeSymbolIndex);
            cfg->nextFreeSymbolIndex -= 8;
            cfg->current_bb->add_IRInstr(IRInstr::int_to_double, DOUBLE, {leftOffset});
        }
        if (rightType == INT) {
            
            rightOffset = to_string(cfg->nextFreeSymbolIndex);
            cfg->nextFreeSymbolIndex -= 8;
            cfg->current_bb->add_IRInstr(IRInstr::int_to_double, DOUBLE, {rightOffset});
        }
    } else {
        lastExprType = INT;
    }

    std::string op = ctx->OP->getText();
    if (op == "+")
        cfg->current_bb->add_IRInstr(IRInstr::add, lastExprType, {leftOffset, rightOffset});
    else
        cfg->current_bb->add_IRInstr(IRInstr::sub, lastExprType, {leftOffset, rightOffset});

    return 0;
}

antlrcpp::Any IRGenVisitor::visitMulDiv(ifccParser::MulDivContext *ctx)
{
    // cout<<"visitMulDiv\n";
    visit(ctx->expr(0));
    Type leftType = lastExprType;
    
    string leftOffset = to_string(cfg->nextFreeSymbolIndex);
    cfg->nextFreeSymbolIndex -= getTypeSize(leftType);
    cfg->current_bb->add_IRInstr(IRInstr::copy, lastExprType, {leftOffset});
    visit(ctx->expr(1));
    Type rightType = lastExprType;
    
    string rightOffset = to_string(cfg->nextFreeSymbolIndex);
    cfg->nextFreeSymbolIndex -= getTypeSize(rightType);
    cfg->current_bb->add_IRInstr(IRInstr::copy, lastExprType, {rightOffset});
    
    if (leftType == DOUBLE || rightType == DOUBLE) {
        lastExprType = DOUBLE;

        if (leftType == INT) {
            cfg->current_bb->add_IRInstr(IRInstr::int_to_double, DOUBLE, {leftOffset, leftOffset});
        }
        if (rightType == INT) {
            cfg->current_bb->add_IRInstr(IRInstr::int_to_double, DOUBLE, {rightOffset, rightOffset});
        }
    } else {
        lastExprType = INT;
    }
    
    std::string op = ctx->OP->getText();
    if (op == "*")
    {
        cfg->current_bb->add_IRInstr(IRInstr::mul, lastExprType, {leftOffset, rightOffset});
    }
    else if (op == "/")
    {
        cfg->current_bb->add_IRInstr(IRInstr::div, lastExprType, {leftOffset, rightOffset});
    }
    else if (op == "%" && lastExprType == INT)
    {
        cfg->current_bb->add_IRInstr(IRInstr::mod, INT, {leftOffset, rightOffset});
    }
    return 0;
}

antlrcpp::Any IRGenVisitor::visitParExpr(ifccParser::ParExprContext *ctx)
{
    // cout<<"visitParExpr\n";
    return visit(ctx->expr());
}

antlrcpp::Any IRGenVisitor::visitNegateExpr(ifccParser::NegateExprContext *ctx)
{
    // cout<<"visitNegateExpr\n";
    visit(ctx->expr());
    cfg->current_bb->add_IRInstr(IRInstr::neg, INT, {});
    return 0;
}

antlrcpp::Any IRGenVisitor::visitNotExpr(ifccParser::NotExprContext *ctx)
{
    visit(ctx->expr());
    cfg->current_bb->add_IRInstr(IRInstr::cmp_eq, INT, {});
    return 0;
}

antlrcpp::Any IRGenVisitor::visitCmpExpr(ifccParser::CmpExprContext *ctx) {
    visit(ctx->expr(0));
    Type leftType = lastExprType;
    
    string leftOffset = to_string(cfg->nextFreeSymbolIndex);
    cfg->nextFreeSymbolIndex -= getTypeSize(leftType);
    cfg->current_bb->add_IRInstr(IRInstr::copy, leftType, {leftOffset});

    visit(ctx->expr(1));
    Type rightType = lastExprType;
    
    string rightOffset = to_string(cfg->nextFreeSymbolIndex);
    cfg->nextFreeSymbolIndex -= getTypeSize(rightType);
    cfg->current_bb->add_IRInstr(IRInstr::copy, rightType, {rightOffset});

    if (leftType == DOUBLE || rightType == DOUBLE) {
        lastExprType = DOUBLE;
        if (leftType == INT)
            cfg->current_bb->add_IRInstr(IRInstr::int_to_double, DOUBLE, {leftOffset});
        if (rightType == INT)
            cfg->current_bb->add_IRInstr(IRInstr::int_to_double, DOUBLE, {rightOffset});
    } else {
        lastExprType = INT;
    }

    // Charger la valeur gauche
    cfg->current_bb->add_IRInstr(IRInstr::ldvar, lastExprType, {leftOffset});

    // Déterminer l'instruction set*
    std::string op = ctx->getText();
    std::string setInstr;
    if (op.find("==") != std::string::npos) setInstr = "sete";
    else if (op.find("!=") != std::string::npos) setInstr = "setne";
    else if (op.find("<=") != std::string::npos) setInstr = "setle";
    else if (op.find(">=") != std::string::npos) setInstr = "setge";
    else if (op.find("<")  != std::string::npos) setInstr = "setl";
    else if (op.find(">")  != std::string::npos) setInstr = "setg";

    // Comparaison finale
    cfg->current_bb->add_IRInstr(IRInstr::cmp_expr, lastExprType, {rightOffset, setInstr});
    lastExprType = INT; // une comparaison retourne toujours un booléen (int)
    return 0;
}


antlrcpp::Any IRGenVisitor::visitCharConstExpr(ifccParser::CharConstExprContext *ctx)
{

    std::string text = ctx->CHAR()->getText(); // exemple : 'A'
    char c = text[1];						   // le caractère réel entre les apostrophes
    string asciiValue = to_string(static_cast<int>(c));
    cfg->current_bb->add_IRInstr(IRInstr::ldconst, INT, {asciiValue});
    lastExprType = INT;
    return 0;
}

antlrcpp::Any IRGenVisitor::visitBitwiseAndExpr(ifccParser::BitwiseAndExprContext *ctx)
{
    visit(ctx->expr(0));
    
    string leftOffset = to_string(cfg->nextFreeSymbolIndex);
    cfg->nextFreeSymbolIndex -= 4;
    cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
    visit(ctx->expr(1));
    
    string rightOffset = to_string(cfg->nextFreeSymbolIndex);
    cfg->nextFreeSymbolIndex -= 4;
    cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
    cfg->current_bb->add_IRInstr(IRInstr::bitwise_and, INT, {leftOffset, rightOffset});
    return 0;
}

antlrcpp::Any IRGenVisitor::visitBitwiseOrExpr(ifccParser::BitwiseOrExprContext *ctx)
{
    visit(ctx->expr(0));
    
    string leftOffset = to_string(cfg->nextFreeSymbolIndex);
    cfg->nextFreeSymbolIndex -= 4;
    cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
    visit(ctx->expr(1));
    
    string rightOffset = to_string(cfg->nextFreeSymbolIndex);
    cfg->nextFreeSymbolIndex -= 4;
    cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
    cfg->current_bb->add_IRInstr(IRInstr::bitwise_or, INT, {leftOffset, rightOffset});
    return 0;
}

antlrcpp::Any IRGenVisitor::visitBitwiseXorExpr(ifccParser::BitwiseXorExprContext *ctx)
{
    visit(ctx->expr(0));
    
    string leftOffset = to_string(cfg->nextFreeSymbolIndex);
    cfg->nextFreeSymbolIndex -= 4;
    cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {leftOffset});
    visit(ctx->expr(1));
    
    string rightOffset = to_string(cfg->nextFreeSymbolIndex);
    cfg->nextFreeSymbolIndex -= 4;
    cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {rightOffset});
    cfg->current_bb->add_IRInstr(IRInstr::bitwise_xor, INT, {leftOffset, rightOffset});
    return 0;
}

antlrcpp::Any IRGenVisitor::visitBlock(ifccParser::BlockContext *ctx)
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

antlrcpp::Any IRGenVisitor::visitIf_stmt(ifccParser::If_stmtContext *ctx)
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

antlrcpp::Any IRGenVisitor::visitWhile_stmt(ifccParser::While_stmtContext *ctx)
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

antlrcpp::Any IRGenVisitor::visitFunctionCall(ifccParser::FunctionCallContext *ctx) 
{
    std::string funcName = ctx->VAR()->getText();

    if (funcName == "putchar") {
        visit(ctx->expr(0));  // Place l'argument dans %eax

        
        string offset = to_string(cfg->nextFreeSymbolIndex);
        cfg->nextFreeSymbolIndex -= 4;
        cfg->current_bb->add_IRInstr(IRInstr::copy, INT, {offset}); // Sauvegarde %eax
        cfg->current_bb->add_IRInstr(IRInstr::call, INT, {"putchar", offset});
        return 0;
    }
    else if (funcName == "getchar") {
        
        string offset = to_string(cfg->nextFreeSymbolIndex);
        cfg->nextFreeSymbolIndex -= 4;
        cfg->current_bb->add_IRInstr(IRInstr::call, INT, {"getchar", offset});
        return 0;
    }

    return 0;
}	
