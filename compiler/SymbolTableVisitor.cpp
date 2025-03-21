#include "SymbolTableVisitor.h"

antlrcpp::Any SymbolTableVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
    std::string varName = ctx->VAR()->getText();

    if (symbolTable.find(varName) != symbolTable.end()) {
        std::cerr << "Erreur : Variable '" << varName << "' déjà déclarée !" << std::endl;
        exit(1);
    }

    symbolTable[varName] = stackOffset;
    stackOffset -= 4;  // Réserver 4 octets pour la variable

    std::cout << "# Déclaration : " << varName << " -> " << symbolTable[varName] << " (%rbp)" << std::endl;

    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitAssignment(ifccParser::AssignmentContext *ctx) {
    std::string varName = ctx->VAR()->getText();

    if (symbolTable.find(varName) == symbolTable.end()) {
        std::cerr << "Erreur : Variable '" << varName << "' utilisée sans être déclarée !" << std::endl;
        exit(1);
    }
    usedVariables.insert(varName);
    this->visit(ctx->expr());  // Visite de l'expression affectée
    return 0;
}


antlrcpp::Any SymbolTableVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
    std::string varName = ctx->getText();
    if (symbolTable.find(varName) == symbolTable.end()) {
        std::cerr << "Erreur : Variable '" << varName << "' utilisée sans être déclarée !" << std::endl;
        exit(1);
    }
    usedVariables.insert(varName);
    return 0;
}


antlrcpp::Any SymbolTableVisitor::visitReturn_stmt(ifccParser::Return_stmtContext *ctx) {
    this->visit(ctx->expr());  // Visite récursive de l'expression de retour
    return 0;
}


// Vérification des variables non utilisées
void SymbolTableVisitor::checkUnusedVariables() {
    for (const auto& pair : symbolTable) {
        const std::string& varName = pair.first;
        if (usedVariables.find(varName) == usedVariables.end()) {
            std::cerr << "# Avertissement : Variable '" << varName << "' déclarée mais jamais utilisée !" << std::endl;
        }
    }
}
