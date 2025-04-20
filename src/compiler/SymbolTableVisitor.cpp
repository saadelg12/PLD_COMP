#include "SymbolTableVisitor.h"

// Visite une déclaration de variable
antlrcpp::Any SymbolTableVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
    std::string varName = ctx->ID()->getText(); // Récupère le nom de la variable
    // Déterminer le type
    std::string typeText = ctx->TYPE()->getText(); // Récupère le type de la variable
    Type varType;
    if (typeText == "int") { // Si le type est "int"
        varType = INT;
    } else if (typeText == "double") { // Si le type est "double"
        varType = DOUBLE;
    } else { // Si le type est inconnu
        std::cerr << "Type inconnu : " << typeText << "\n";
        exit(1);
    }
    // Vérifier si la variable existe déjà dans le scope courant
    if (currentScope->contains(varName)) {
        std::cerr << "Erreur : Variable '" << varName << "' déjà déclarée dans ce scope !" << std::endl;
        exit(1);
    }
    
    // Insérer la variable avec l'offset actuel
    int& offset = functions[currentFunction].stackOffset; // Récupère l'offset actuel
    currentScope->insert(varName, offset, varType); // Insère la variable dans la table des symboles
    offset -= getTypeSize(varType); // Met à jour l'offset en fonction de la taille du type

    std::cout << "# Déclaration : " << varName << " -> "
              << currentScope->get(varName).symbolOffset << " (%rbp)" << std::endl;

    return 0;
}

// Visite une assignation de variable
antlrcpp::Any SymbolTableVisitor::visitAssignment(ifccParser::AssignmentContext *ctx) {
    std::string varName = ctx->ID()->getText(); // Récupère le nom de la variable
    Symbol var = currentScope->get(varName); // Récupère la variable dans la table des symboles
    if (var.symbolOffset==-1) { // Si la variable n'est pas déclarée
        std::cerr << "Erreur : Variable '" << varName << "' utilisée sans être déclarée !" << std::endl;
        exit(1);
    }
    this->visit(ctx->expr()); // Visite l'expression assignée
    return 0;
}

// Visite une expression contenant un identifiant
antlrcpp::Any SymbolTableVisitor::visitIdExpr(ifccParser::IdExprContext *ctx) {
    std::string varName = ctx->ID()->getText(); // Récupère le nom de la variable

    Symbol var = currentScope->get(varName); // Récupère la variable dans la table des symboles
    if (var.symbolOffset==-1) { // Si la variable n'est pas déclarée
        std::cerr << "Erreur : Variable '" << varName << "' utilisée sans être déclarée !" << std::endl;
        exit(1);
    }
    functions[currentFunction].usedVariables.insert(var.symbolOffset); // Marque la variable comme utilisée
    return 0;
}

// Visite une instruction de retour
antlrcpp::Any SymbolTableVisitor::visitReturn_stmt(ifccParser::Return_stmtContext *ctx) {
    if (not hasReturn) { // Si la fonction n'a pas encore de retour
        hasReturn = true;
    } 
    this->visit(ctx->expr()); // Visite l'expression à retourner
    return 0;
}

// Visite un bloc de code
antlrcpp::Any SymbolTableVisitor::visitBlock(ifccParser::BlockContext *ctx) {
    
    SymbolTable * newSymbolTable = new SymbolTable(); // Crée une nouvelle table des symboles pour le bloc
    newSymbolTable->parent = this->currentScope; // Définit le parent de la nouvelle table
    this->currentScope = newSymbolTable; // Change la portée actuelle
    functions[currentFunction].symbolTable.push_back(currentScope); // Ajoute la table au contexte de la fonction
    for (auto stmt : ctx->stmt()) {  // Itère sur chaque instruction du bloc
        this->visit(stmt);  // Visite chaque instruction (déclaration, assignation, retour)
    }
    checkUnusedVariables(); // Vérifie les variables non utilisées
    currentScope = currentScope->parent; // Restaure la portée précédente 
    
    return 0;
}

// Visite une définition de fonction
antlrcpp::Any SymbolTableVisitor::visitFunctionDef(ifccParser::FunctionDefContext *ctx) {
    Type functionReturnType = get_type(ctx->TYPE()->getText()); // Récupère le type de retour de la fonction
    std::string functionName = ctx->ID()->getText(); // Récupère le nom de la fonction
    currentFunction = functionName; // Définit la fonction actuelle
    functions[currentFunction].returnType = functionReturnType; // Définit le type de retour
    functions[currentFunction].stackOffset = -4; // Initialise l'offset de la pile
    SymbolTable* st = new SymbolTable(); // Crée une nouvelle table des symboles
    if (ctx->parameter_list()) { // Vérifie si la fonction a des paramètres
        for (auto param : ctx->parameter_list()->parameter()) { // Itère sur les paramètres
            Symbol s;
            std::string argName = param->ID()->getText(); // Récupère le nom du paramètre
            std::string argType = param->TYPE()->getText(); // Récupère le type du paramètre
            
            st->insert(argName, functions[currentFunction].stackOffset, get_type(argType)); // Insère le paramètre dans la table
            functions[currentFunction].stackOffset -= 4; // Met à jour l'offset
        }
        functions[currentFunction].symbolTable.push_back(st); // Ajoute la table au contexte de la fonction
        st->parent = nullptr; // Définit le parent de la table
    } else {
        st = nullptr; // Si pas de paramètres, la table est nulle
        functions[currentFunction].symbolTable.push_back(st);
    }
    currentScope = st; // Définit la portée actuelle
    visit(ctx->block()); // Visite le bloc de la fonction
    checkHasReturn(); // Vérifie si la fonction a un retour
    if (hasReturn == false) { // Si pas de retour
        std::cerr << "Erreur : Fonction '" << functionName << "' sans `return` !" << std::endl;
        exit(1);
    }
    hasReturn = false; // Réinitialise le flag de retour
    return 0;
}

// Visite la fonction main
antlrcpp::Any SymbolTableVisitor::visitMainFunction(ifccParser::MainFunctionContext *ctx) {
    Type functionReturnType = get_type(ctx->TYPE()->getText()); // Récupère le type de retour de main
    std::string functionName = "main"; // Nom de la fonction main
    currentFunction = functionName; // Définit la fonction actuelle
    functions[currentFunction].returnType = functionReturnType; // Définit le type de retour
    functions[currentFunction].stackOffset = -4; // Initialise l'offset de la pile
    SymbolTable* st = new SymbolTable(); // Crée une nouvelle table des symboles
    
    st = nullptr; // Pas de paramètres pour main
    functions[currentFunction].symbolTable.push_back(st);
    
    currentScope = st; // Définit la portée actuelle
    visit(ctx->block()); // Visite le bloc de main
    checkHasReturn(); // Vérifie si main a un retour
    if (hasReturn == false) { // Si pas de retour
        std::cerr << "Erreur : Main '" << functionName << "' sans `return` !" << std::endl;
        exit(1);
    }
    hasReturn = false; // Réinitialise le flag de retour
    return 0;
}

// Visite un appel de fonction
antlrcpp::Any SymbolTableVisitor::visitFunctionCall(ifccParser::FunctionCallContext *ctx) {
    std::string functionName = ctx->ID()->getText(); // Récupère le nom de la fonction
    if (functionName !="getchar" && functionName !="putchar" ){ // Vérifie si ce n'est pas une fonction standard
        if (functions.find(functionName) == functions.end()) { // Vérifie si la fonction est déclarée
            std::cerr << "Erreur : Fonction '" << functionName << "' non déclarée !" << std::endl;
            exit(1);
        }
    
        int i =0;
        while (ctx->expr(i)) { // Itère sur les arguments passés
            visit(ctx->expr(i)); // Visite chaque argument
            i++;
        }
        if(functions[functionName].symbolTable.at(0) != nullptr && functions[functionName].symbolTable.at(0)->table.size() != i){ // Vérifie le nombre d'arguments
            std::cerr << "Erreur : Fonction '" << functionName << "' prend "<< functions[functionName].symbolTable.size()<< " paramètres et non pas "<<i<< std::endl;
            exit(1);
        }
        // Vérifie si la fonction ne prend pas de paramètres mais des arguments sont passés
        if (functions[functionName].symbolTable.at(0) == nullptr && i != 0){
            std::cerr << "Erreur : Fonction '" << functionName << "' ne prend pas de paramètres. Vous avez passé " << i << " paramètres." << std::endl;
            exit(1);
        }
    
    }
    
    return 0;
}

// Visite une déclaration de fonction
antlrcpp::Any SymbolTableVisitor::visitFunctionDec(ifccParser::FunctionDecContext *ctx) {
    std::string functionName = ctx->ID()->getText(); // Récupère le nom de la fonction
    if (functions.find(functionName) == functions.end()) { // Vérifie si la fonction n'est pas déjà déclarée
        // Ajoute la fonction à la map des fonctions déclarées
        Type functionReturnType = get_type(ctx->TYPE()->getText()); // Récupère le type de retour
        functions[functionName].returnType = functionReturnType; // Définit le type de retour
    } else {
        std::cerr << "Erreur : Fonction '" << functionName << "' déjà déclarée !" << std::endl;
        exit(1);
    }
    return 0;
}

// Vérifie les variables non utilisées
void SymbolTableVisitor::checkUnusedVariables() {    
    // Accéder à la table des symboles dans la portée actuelle
    if(currentScope==nullptr) return; // Si la portée est nulle, rien à vérifier
    const auto& symbolTable = currentScope->table; // Récupère la table des symboles
    for (const auto& entry : symbolTable) { // Itère sur chaque entrée de la table
        const auto& var = entry.second;
        int found = 0;
        if (functions[currentFunction].usedVariables.find(var.symbolOffset) == functions[currentFunction].usedVariables.end()) { // Si la variable n'est pas utilisée
            std::cout << "# Avertissement : Variable '" << var.symbolName << "' déclarée mais jamais utilisée !" << std::endl;
            
        }
        
    }
}

// Vérifie si une fonction a un retour
void SymbolTableVisitor::checkHasReturn() {
    if (hasReturn==false) { // Si pas de retour
        std::cerr << "# Avertissement : Fonction sans `return` !" << std::endl;
    }else{
        std::cout << "# Fonction avec `return` !" << std::endl;}
}
