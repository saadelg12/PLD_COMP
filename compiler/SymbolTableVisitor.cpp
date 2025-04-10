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

antlrcpp::Any SymbolTableVisitor::visitFunction_decl(ifccParser::Function_declContext *ctx) {
    std::string funcName = ctx->VAR()->getText();

    // Vérification : fonction déjà déclarée ?
    if (currentScope && currentScope->contains(funcName)) {
        std::cerr << "Erreur : Fonction '" << funcName << "' déjà définie !" << std::endl;
        exit(1);
    }

    std::cout << "# Définition de la fonction " << funcName << std::endl;

    // Création d'une nouvelle SymbolTable pour la fonction
    SymbolTable* functionScope = new SymbolTable();
    functionScope->parent = currentScope; // rattachement au scope global (ou précédent)
    currentScope = functionScope;
    symbolTables.push_back(currentScope);

    // Reset offset local pour les variables/params de la fonction
    stackOffset = -4;

    // Gestion des paramètres de la fonction
    if(ctx->param_list()) {
        for(size_t i = 0; i < ctx->param_list()->VAR().size(); i++) {
            std::string paramName = ctx->param_list()->VAR(i)->getText();

            if (currentScope->contains(paramName)) {
                std::cerr << "Erreur : Paramètre '" << paramName << "' déjà défini dans cette fonction !" << std::endl;
                exit(1);
            }

            currentScope->insert(paramName, stackOffset, INT); // on suppose que les params sont tous INT
            std::cout << "# Paramètre : " << paramName << " -> " << stackOffset << " (%rbp)" << std::endl;
            stackOffset -= 4;
        }
    }

    // Visite du block de la fonction
    this->visit(ctx->block());

    // Vérif return obligatoire
    checkHasReturn();

    // Reset hasReturn pour les prochaines fonctions
    hasReturn = false;

    // Remonter d'un scope
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

