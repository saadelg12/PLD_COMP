#include "SymbolTableVisitor.h"

antlrcpp::Any SymbolTableVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
    std::string varName = ctx->VAR()->getText();

    // Vérifier si la variable existe déjà dans le scope courant
    if (currentScope->contains(varName)) {
        std::cerr << "Erreur : Variable '" << varName << "' déjà déclarée dans ce scope !" << std::endl;
        exit(1);
    }

    // Insérer la variable avec l'offset actuel
    currentScope->insert(varName, stackOffset,INT);
    stackOffset -= 4;  // Réserver 4 octets pour la variable

    std::cout << "# Déclaration : " << varName << " -> " 
              << currentScope->get(varName).symbolOffset << " (%rbp)" << std::endl;
    if(ctx->expr()){
        this->visit(ctx->expr()); 
    }
    
    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitAssignment(ifccParser::AssignmentContext *ctx) {
    std::string varName = ctx->VAR()->getText();
    Symbol var = currentScope->get(varName);
    if (var.symbolOffset==-1) {
        std::cerr << "Erreur : Variable '" << varName << "' utilisée sans être déclarée !" << std::endl;
        exit(1);
    }
    this->visit(ctx->expr()); 
    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
    std::string varName = ctx->VAR()->getText();
    Symbol var = currentScope->get(varName);
    if (var.symbolOffset==-1) {
        std::cerr << "Erreur : Variable '" << varName << "' utilisée sans être déclarée !" << std::endl;
        exit(1);
    }
    usedVariables.insert(var.symbolOffset);
    return 0;
}


antlrcpp::Any SymbolTableVisitor::visitReturn_stmt(ifccParser::Return_stmtContext *ctx) {
    if (hasReturn==false) {
        hasReturn = true;
    } 
    this->visit(ctx->expr()); // Visiter l'expression à retourner
    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitBlock(ifccParser::BlockContext *ctx) {
    
    SymbolTable * newSymbolTable = new SymbolTable();
    newSymbolTable->parent = this->currentScope;
    this->currentScope = newSymbolTable;
    symbolTables.push_back(currentScope);
    for (auto stmt : ctx->stmt()) {  // iterate over each statement in the list
        this->visit(stmt);  // visit each statement (declaration, assignment, return)
    }
    checkUnusedVariables();
    currentScope = currentScope->parent;
    
    
    return 0;
}

void SymbolTableVisitor::checkUnusedVariables() {
    // Accéder à la table des symboles dans la portée actuelle
    if(currentScope==nullptr) return;
    const auto& symbolTable = currentScope->table;
    for (const auto& entry : symbolTable) {
        const auto& var = entry.second;
        int found = 0;
        if (usedVariables.find(var.symbolOffset) == usedVariables.end()) {
            std::cout << "# Avertissement : Variable '" << var.symbolName << "' déclarée mais jamais utilisée !" << std::endl;
            
        }
        
    }
}


void SymbolTableVisitor::checkHasReturn() {
    if (hasReturn==false) {
        std::cerr << "# Avertissement : Fonction sans `return` !" << std::endl;
    }
}