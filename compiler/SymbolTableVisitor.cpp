#include "SymbolTableVisitor.h"

antlrcpp::Any SymbolTableVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
    std::string varName = ctx->VAR()->getText();

    // Vérifier si la variable existe déjà dans le scope courant
    if (currentScope->contains(varName)) {
        std::cerr << "Erreur : Variable '" << varName << "' déjà déclarée dans ce scope !" << std::endl;
        exit(1);
    }

    // Insérer la variable avec l'offset actuel
    int& offset = stackOffsets[currentFunction];
    currentScope->insert(varName, offset, INT);
    offset -= 4;

    std::cout << "# Déclaration : " << varName << " -> "
              << currentScope->get(varName).symbolOffset << " (%rbp)" << std::endl;

    return 0;
}


antlrcpp::Any SymbolTableVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
    std::string varName = ctx->VAR()->getText();

    if (currentScope->get(varName).symbolOffset==-1) {
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

antlrcpp::Any SymbolTableVisitor::visitBlock(ifccParser::BlockContext *ctx) {
    
    SymbolTable * newSymbolTable = new SymbolTable();
    newSymbolTable->parent = this->currentScope;
    this->currentScope = newSymbolTable;
    functionSymbolTables[currentFunction].push_back(currentScope);
    for (auto stmt : ctx->stmt()) {  // iterate over each statement in the list
        this->visit(stmt);  // visit each statement (declaration, assignment, return)
    }
    // checkUnusedVariables();
    currentScope = currentScope->parent;    
    
    return 0;
}


antlrcpp::Any SymbolTableVisitor::visitFunctionDef(ifccParser::FunctionDefContext *ctx) {
    std::string functionName = ctx->VAR()->getText();
    currentFunction = functionName;
    functionsMap[currentFunction] = ctx->TYPE()->getText();  // Type de la fonction

    SymbolTable * st;
    currentScope = new SymbolTable();  // Racine
    
    stackOffsets[currentFunction] = -4;

    int i = 0; // Start index at 0
    if (ctx->parameter_list()) { // Check if parameter_list exists
        for (auto param : ctx->parameter_list()->parameter()) {
            std::string argName = param->VAR()->getText(); // Get the variable name
            if (currentScope->contains(argName)) {
                std::cerr << "Erreur : Variable '" << argName << "' déjà déclarée dans ce scope !" << std::endl;
                exit(1);
            }
            currentScope->insert(argName, stackOffsets[currentFunction], INT);
            stackOffsets[currentFunction] -= 4;
            i++;
        }
    }
    functionSymbolTables[currentFunction].push_back(currentScope);
    
    hasReturn = false;
    visit(ctx->block());

    // Optionnel : vérifications
    //checkUnusedVariables(functionName);
    checkHasReturn();
    hasReturn = false;

    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitFunctionCall(ifccParser::FunctionCallContext *ctx) {
    std::string functionName = ctx->VAR()->getText();
    if (functionsMap.find(functionName) == functionsMap.end()) {
        std::cerr << "Erreur : Fonction '" << functionName << "' non déclarée !" << std::endl;
        exit(1);
    }
    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitFunctionDec(ifccParser::FunctionDecContext *ctx) {
    std::string functionName = ctx->VAR()->getText();
    if (functionsMap.find(functionName) == functionsMap.end()) {
        // On ajoute la fonction à la map des fonctions déclarées
        functionsMap[functionName] = ctx->TYPE()->getText();  // Type de la fonction
    } else {
        std::cerr << "Erreur : Fonction '" << functionName << "' déjà déclarée !" << std::endl;
        exit(1);
    }
    return 0;
}

void SymbolTableVisitor::checkUnusedVariables() {
    
    // // Accéder à la table des symboles dans la portée actuelle
    // const auto& symbolTable = currentScope->table;
    // for (const auto& entry : symbolTable) {
    //     const auto& varName = entry.first;
    //     if (usedVariables.find(varName) == usedVariables.end()) {
    //         std::cerr << "# Avertissement : Variable '" << varName << "' déclarée mais jamais utilisée !" << std::endl;
    //     }
    // }
}


void SymbolTableVisitor::checkHasReturn() {
    if (not hasReturn) {
        std::cerr << "# Avertissement : Fonction sans `return` !" << std::endl;
        exit(1);
    }
}