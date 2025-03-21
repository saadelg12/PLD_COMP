#include "CodeGenVisitor.h"

// Visite du programme principal
antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
    #ifdef __APPLE__
    std::cout << ".globl _main\n";
    std::cout << " _main: \n";
    #else
    std::cout << ".globl main\n";
    std::cout << " main: \n";
    #endif

    // Prologue
    std::cout << "    pushq %rbp\n";        
    std::cout << "    movq %rsp, %rbp\n";   

    bool hasReturn = false;
    for (auto stmt : ctx->stmt()) {
        if (stmt->return_stmt() != nullptr) {
            hasReturn = true;
            break;
        }
    }

    for (auto stmt : ctx->stmt()) {
        this->visit(stmt);
    }

    // Ajout de `return 0;` implicite si nécessaire
    if (!hasReturn) {
        std::cout << "    movl $0, %eax   # return 0 implicite\n";
        std::cout << "    popq %rbp\n";
        std::cout << "    ret\n";
    }

    return 0;
}


// Gérer les déclarations (ex: int a = 42;)
antlrcpp::Any CodeGenVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx)
{   
    if (ctx->expr()) {  
        std::string varName = ctx->VAR()->getText();
        int offset = (*symbolTable)[varName];

        if (auto constExpr = dynamic_cast<ifccParser::ConstExprContext*>(ctx->expr())) {
            int value = std::stoi(constExpr->getText());
            std::cout << "    movl $" << value << ", " << offset << "(%rbp)   # Init " << varName << "\n";
        }
    }
    return 0;
}

// Gérer les affectations (ex: a = 5;)
antlrcpp::Any CodeGenVisitor::visitAssignment(ifccParser::AssignmentContext *ctx)
{
    std::string varName = ctx->VAR()->getText();
    int offset = (*symbolTable)[varName];  

    if (auto constExpr = dynamic_cast<ifccParser::ConstExprContext*>(ctx->expr())) {
        int value = std::stoi(constExpr->getText());
        std::cout << "    movl $" << value << ", " << offset << "(%rbp)   # Assign " << value << " to " << varName << "\n";
    } 
    else if (auto varExpr = dynamic_cast<ifccParser::VarExprContext*>(ctx->expr())) {
        std::string varNameSrc = varExpr->getText();
        int offsetSrc = (*symbolTable)[varNameSrc];
        std::cout << "    movl " << offsetSrc << "(%rbp), %eax   # Load " << varNameSrc << " into %eax\n";
        std::cout << "    movl %eax, " << offset << "(%rbp)   # Store in " << varName << "\n";
    }

    return 0;
}

// Gérer les `return`
antlrcpp::Any CodeGenVisitor::visitReturn_stmt(ifccParser::Return_stmtContext *ctx)
{
    visit(ctx->expr());  // Met le résultat dans %eax
    std::cout << "    popq %rbp\n";
    std::cout << "    ret\n";
    return 0;
}


// Visite d'un entier constant
antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) {
    int value = std::stoi(ctx->getText());
    std::cout << "    movl $" << value << ", %eax   # Load constant " << value << " into %eax\n";
    return 0;
}

// Visite d'une variable
antlrcpp::Any CodeGenVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
    std::string varName = ctx->getText();
    int offset = (*symbolTable)[varName];
    std::cout << "    movl " << offset << "(%rbp), %eax   # Load variable " << varName << " into %eax\n";
    return 0;
}

antlrcpp::Any CodeGenVisitor::visitAddSub(ifccParser::AddSubContext *ctx) {
    visit(ctx->expr(0));                       // Résultat gauche dans %eax
    std::cout << "    movl %eax, %ebx\n";      // Stocke gauche dans %ebx
    visit(ctx->expr(1));                       // Résultat droit dans %eax

    std::string op = ctx->getText();
    if (op.find('+') != std::string::npos) {
        std::cout << "    addl %ebx, %eax   # Addition\n";
    } else if (op.find('-') != std::string::npos) {
        std::cout << "    movl %eax, %ecx\n";
        std::cout << "    movl %ebx, %eax\n";
        std::cout << "    subl %ecx, %eax   # Soustraction\n";
    }
    return 0;
}


antlrcpp::Any CodeGenVisitor::visitMulDiv(ifccParser::MulDivContext *ctx) {
    visit(ctx->expr(0));                       // Résultat gauche dans %eax
    std::cout << "    movl %eax, %ebx\n";      // Stocke gauche dans %ebx
    visit(ctx->expr(1));                       // Résultat droit dans %eax

    std::string op = ctx->getText();
    if (op.find('*') != std::string::npos) {
        std::cout << "    imull %ebx, %eax  # Multiplication\n";
    } else if (op.find('/') != std::string::npos) {
        std::cout << "    movl %eax, %ecx\n";  // divisor
        std::cout << "    movl %ebx, %eax\n";  // dividend
        std::cout << "    cltd\n";
        std::cout << "    idivl %ecx        # Division\n";
    }
    return 0;
}




antlrcpp::Any CodeGenVisitor::visitParenthesized(ifccParser::ParenthesizedContext *ctx) {
    return visit(ctx->expr()); // Récupère directement l'expression interne
}
