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

antlrcpp::Any SymbolTableVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
    std::string varName = ctx->VAR()->getText();

    if (symbolTable.find(varName) == symbolTable.end()) {
        std::cerr << "Erreur : Variable '" << varName << "' utilisée sans être déclarée !" << std::endl;
        exit(1);
    }

    usedVariables.insert(varName);
    return 0;
}


antlrcpp::Any SymbolTableVisitor::visitReturn_stmt(ifccParser::Return_stmtContext *ctx) {
    if (not hasReturn) {
        hasReturn = true;
    } 
    this->visit(ctx->expr()); // Visiter l'expression à retourner
    return 0;
}

void SymbolTableVisitor::checkUnusedVariables() {
    for (const auto& entry : symbolTable) {
        const auto& varName = entry.first;
        if (usedVariables.find(varName) == usedVariables.end()) {
            std::cerr << "# Avertissement : Variable '" << varName << "' déclarée mais jamais utilisée !" << std::endl;
        }
    }
}


void SymbolTableVisitor::checkHasReturn() {
    if (not hasReturn) {
        std::cerr << "# Avertissement : Fonction sans `return` !" << std::endl;
        exit(1);
    }
}



antlrcpp::Any SymbolTableVisitor::visitFunction_def(ifccParser::Function_defContext *ctx) {
    std::string functionName = ctx->VAR()->getText();
    std::string returnType = ctx->type()->getText();

    // Check if the function is already defined
    if (functionTable.find(functionName) != functionTable.end()) {
        std::cerr << "Erreur : Fonction '" << functionName << "' déjà définie !" << std::endl;
        exit(1);
    }

    // Parse parameters
    std::vector<std::pair<std::string, std::string>> parameters;
    if (ctx->param_list()) {
        for (auto paramCtx : ctx->param_list()->param()) {
            std::string paramType = paramCtx->type()->getText();
            std::string paramName = paramCtx->VAR()->getText();
            parameters.push_back({paramType, paramName});
        }
    }

    // Add function to the function table
    functionTable[functionName] = {returnType, parameters};

    // Visit each statement in the function body
    for (auto stmt : ctx->stmt()) {
        visit(stmt); // Visit each statement individually
    }

    return 0;
}
