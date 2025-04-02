#include "CodeGenVisitor.h"

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
    #ifdef __APPLE__
    std::cout<< ".globl _main\n" ;
    std::cout<< " _main: \n" ;
    #else
    std::cout<< ".globl main\n" ;
    std::cout<< " main: \n" ;
    #endif

    // Prologue
    std::cout << "    pushq %rbp\n";        // save %rbp on the stack
    std::cout << "    movq %rsp, %rbp\n";   // define %rbp for the current function

    for (auto stmt : ctx->stmt()) {  // iterate over each statement in the list
        this->visit(stmt);  // visit each statement (declaration, assignment, return)
    }
        
    // Epilogue
    // std::cout << ".end:\n";                 // Label for the end of the program
    std::cout << "    popq %rbp\n";         // restore %rbp from the stack
    std::cout << "    ret\n";               // return to the caller
    return 0;
}

antlrcpp::Any CodeGenVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx)
{   
    std::string varName = ctx->VAR()->getText();  // Récupérer le nom de la variable
    int offset = currentScope->get(varName);
    if (ctx->expr()) {
        visit(ctx->expr());
        std::cout << "    movl %eax, " << offset << "(%rbp)   # Initialisation de " << varName << "\n"; 
    }         
    
    return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignment(ifccParser::AssignmentContext *ctx) {
    std::string varName = ctx->VAR()->getText();  // Récupérer le nom de la variable assignée

    int offset = currentScope->get(varName);
    
    antlrcpp::Any value = visit(ctx->expr());  // On visite l'expression à droite et récupère sa valeur

    std::cout << "    movl %eax, " << offset << "(%rbp)   # Affectation de " << varName << "\n";

    return value;
}

antlrcpp::Any CodeGenVisitor::visitReturn_stmt(ifccParser::Return_stmtContext *ctx) {
    visit(ctx->expr());
    std::cout << "    leave\n";  // Equivalent à `movq %rbp, %rsp` suivi de `popq %rbp`
    std::cout << "    ret\n";    // Retourner à l'appelant     
    return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
    std::string varName = ctx->VAR()->getText();
    int offset = currentScope->get(varName);
    if( offset != -1){
        std::cout << "    movl " << offset << "(%rbp), %eax   # Charger " << varName << " dans %eax\n";
    }
    return 0;
}

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) {
    int value = std::stoi(ctx->CONST()->getText());
    std::cout << "    movl $" << value << ", %eax   # Charger la constante " << value << " dans %eax\n";
    return 0;
}

antlrcpp::Any CodeGenVisitor::visitAddSub(ifccParser::AddSubContext *ctx) {
    // Partie gauche %eax
    visit(ctx->expr(0));

    // Sauvegarde dans temp
    tempVarOffset -= 4;
    int leftOffset = tempVarOffset;
    std::cout << "    movl %eax, " << leftOffset << "(%rbp)   # Save lhs into temp\n";

    // Partie droite → %eax
    visit(ctx->expr(1));

    // Sauvegarde aussi la droite (nécessaire pour soustraction)
    tempVarOffset -= 4;
    int rightOffset = tempVarOffset;
    std::cout << "    movl %eax, " << rightOffset << "(%rbp)   # Save rhs into temp\n";

    std::string op = ctx->OP->getText();
    if (op == "+") {
        std::cout << "    movl " << leftOffset << "(%rbp), %eax   # Load lhs\n";
        std::cout << "    addl " << rightOffset << "(%rbp), %eax   # lhs + rhs\n";
    } else if (op == "-") {
        std::cout << "    movl " << leftOffset << "(%rbp), %eax   # Load lhs\n";
        std::cout << "    subl " << rightOffset << "(%rbp), %eax   # lhs - rhs\n";
    }

    return 0;
}



antlrcpp::Any CodeGenVisitor::visitMulDiv(ifccParser::MulDivContext *ctx) {
    // Partie gauche dans %eax
    visit(ctx->expr(0));
    tempVarOffset -= 4;
    int leftOffset = tempVarOffset;
    std::cout << "    movl %eax, " << leftOffset << "(%rbp)   # Save lhs into temp\n";

    // Partie droite dans %eax
    visit(ctx->expr(1));
    tempVarOffset -= 4;
    int rightOffset = tempVarOffset;
    std::cout << "    movl %eax, " << rightOffset << "(%rbp)   # Save rhs into temp\n";

    std::string op = ctx->getText();
    if (ctx->OP->getText() == "*") {
        std::cout << "    movl " << leftOffset << "(%rbp), %eax\n";
        std::cout << "    imull " << rightOffset << "(%rbp), %eax  # eax = lhs * rhs\n";
    } else {
        std::cout << "    movl " << leftOffset << "(%rbp), %eax   # dividend\n";
        std::cout << "    cltd\n";
        std::cout << "    idivl " << rightOffset << "(%rbp)   # eax = lhs / rhs\n";
        if (ctx->OP->getText() == "%") {
            std::cout << "    movl %edx, %eax   # Pour modulo, on récupère le reste dans edx\n";
        }
    }

    return 0;
}

antlrcpp::Any CodeGenVisitor::visitParExpr(ifccParser::ParExprContext *ctx) {
    return visit(ctx->expr()); // Récupère directement l'expression interne
}

antlrcpp::Any CodeGenVisitor::visitNegateExpr(ifccParser::NegateExprContext *ctx) {
    visit(ctx->expr());  // Résultat de l'expression dans %eax
    std::cout << "    negl %eax   # Negation\n";
    return 0;
}

antlrcpp::Any CodeGenVisitor::visitNotExpr(ifccParser::NotExprContext *ctx) {
    visit(ctx->expr());  // résultat de l'expression dans %eax

    // Comparer à zéro, résultat dans %eax : si eax == 0 → 1 ; sinon → 0
    std::cout << "    cmpl $0, %eax   # Comparaison avec zéro pour !\n";
    std::cout << "    movl $0, %eax\n";
    std::cout << "    sete %al        # Mettre %al à 1 si égal (eax=0), sinon 0\n";

    return 0;
}


antlrcpp::Any CodeGenVisitor::visitCmpExpr(ifccParser::CmpExprContext *ctx) {
    visit(ctx->expr(0)); // lhs → %eax

    tempVarOffset -= 4;
    int lhsOffset = tempVarOffset;
    std::cout << "    movl %eax, " << lhsOffset << "(%rbp)\n";

    visit(ctx->expr(1)); // rhs → %eax

    tempVarOffset -= 4;
    int rhsOffset = tempVarOffset;
    std::cout << "    movl %eax, " << rhsOffset << "(%rbp)\n";

    std::cout << "    movl " << lhsOffset << "(%rbp), %eax\n";
    std::cout << "    cmpl " << rhsOffset << "(%rbp), %eax\n";

    std::string op = ctx->getText();
    std::string setInstr;

    if (op.find("==") != std::string::npos)      setInstr = "sete";
    else if (op.find("!=") != std::string::npos) setInstr = "setne";
    else if (op.find("<=") != std::string::npos) setInstr = "setle";
    else if (op.find(">=") != std::string::npos) setInstr = "setge";
    else if (op.find("<") != std::string::npos)  setInstr = "setl";
    else if (op.find(">") != std::string::npos)  setInstr = "setg";

    std::cout << "    " << setInstr << " %al\n";
    std::cout << "    movzx %al, %eax\n";

    return 0;
}


antlrcpp::Any CodeGenVisitor::visitCharConstExpr(ifccParser::CharConstExprContext *ctx) {
    std::string text = ctx->CHAR()->getText(); // exemple : "'A'"
    char c = text[1]; // le caractère réel entre les apostrophes
    int asciiValue = static_cast<int>(c);
    std::cout << "    movl $" << asciiValue << ", %eax   # Char '" << c << "' (ASCII " << asciiValue << ")\n";
    return 0;
}

antlrcpp::Any CodeGenVisitor::visitBitwiseExpr(ifccParser::BitwiseExprContext *ctx) {
    // Visiter partie gauche %eax
    visit(ctx->expr(0));
    tempVarOffset -= 4;
    int leftOffset = tempVarOffset;
    std::cout << "    movl %eax, " << leftOffset << "(%rbp)   # Save lhs into temp\n";

    // Visiter partie droite %eax
    visit(ctx->expr(1));
    tempVarOffset -= 4;
    int rightOffset = tempVarOffset;
    std::cout << "    movl %eax, " << rightOffset << "(%rbp)   # Save rhs into temp\n";

    // Recharger lhs
    std::cout << "    movl " << leftOffset << "(%rbp), %eax\n";

    // Trouver l'opérateur entre les deux enfants
    std::string op = ctx->getText();
    if (op.find("&") != std::string::npos) {
        std::cout << "    andl " << rightOffset << "(%rbp), %eax   # lhs & rhs\n";
    } else if (op.find("|") != std::string::npos) {
        std::cout << "    orl " << rightOffset << "(%rbp), %eax   # lhs | rhs\n";
    } else if (op.find("^") != std::string::npos) {
        std::cout << "    xorl " << rightOffset << "(%rbp), %eax   # lhs ^ rhs\n";
    }

    return 0;
}

antlrcpp::Any CodeGenVisitor::visitBlock(ifccParser::BlockContext *ctx) 
{
    SymbolTable * newSymbolTable = new SymbolTable();
    newSymbolTable->parent = this->currentScope;
    this->currentScope = newSymbolTable;
    
    for (auto stmt : ctx->stmt()) {  // iterate over each statement in the list
        this->visit(stmt);  // visit each statement (declaration, assignment, return)
    }
    currentScope = currentScope->parent;
    delete newSymbolTable;
    return 0;
}

antlrcpp::Any CodeGenVisitor::visitFunction_call(ifccParser::Function_callContext *ctx) {
    std::string funcName = ctx->FUNC()->getText();

    if (funcName == "putchar") {
        antlrcpp::Any value = visit(ctx->expr());  // Évaluer l'argument
        std::cout << "    movl %eax, %edi   # Argument pour putchar\n";
        std::cout << "    call putchar      # Appel de putchar\n";
    } 
    else if (funcName == "getchar") {
        std::cout << "    call getchar      # Appel de getchar\n";
        std::cout << "    movl %eax, -4(%rbp)  # Stocker la valeur lue\n";
    }

    return 0;
}


