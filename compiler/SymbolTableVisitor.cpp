#include "SymbolTableVisitor.h"

antlrcpp::Any SymbolTableVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
    std::string varName = ctx->VAR()->getText();

    // Vérifier si la variable existe déjà dans le scope courant
    if (currentScope->contains(varName)) {
        std::cerr << "Erreur : Variable '" << varName << "' déjà déclarée dans ce scope !" << std::endl;
        exit(1);
    }
    
    // Insérer la variable avec l'offset actuel
    int& offset = functions[currentFunction].stackOffset;
    currentScope->insert(varName, offset, INT);
    offset -= 4;

    std::cout << "# Déclaration : " << varName << " -> "
              << currentScope->get(varName).symbolOffset << " (%rbp)" << std::endl;

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
    functions[currentFunction].usedVariables.insert(var.symbolOffset);
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
    functions[currentFunction].symbolTable.push_back(currentScope);
    for (auto stmt : ctx->stmt()) {  // iterate over each statement in the list
        this->visit(stmt);  // visit each statement (declaration, assignment, return)
    }
    checkUnusedVariables();
    currentScope = currentScope->parent; // Restore the previous scope 
    
    return 0;
}


antlrcpp::Any SymbolTableVisitor::visitFunctionDef(ifccParser::FunctionDefContext *ctx) {
    Type functionReturnType = get_type(ctx->TYPE()->getText());
    std::string functionName = ctx->VAR()->getText();
    currentFunction = functionName;
    functions[currentFunction].returnType = functionReturnType;
    //SymbolTable* st1 = new SymbolTable();
    functions[currentFunction].stackOffset = -4;
    SymbolTable* st = new SymbolTable();
    if (ctx->parameter_list()) { // Check if parameter_list exists
        //std::cout<<"Function has parameters"<<std::endl;
        
        for (auto param : ctx->parameter_list()->parameter()) {
            Symbol s;
            std::string argName = param->VAR()->getText(); // Get the variable name
            std::string argType = param->TYPE()->getText(); // Get the variable name
            // if (currentScope->contains(argName)) {
            //     std::cerr << "Erreur : Variable '" << argName << "' déjà déclarée dans ce scope !" << std::endl;
            //     exit(1);
            // }
        
            
            st->insert(argName, functions[currentFunction].stackOffset,get_type(argType));
            functions[currentFunction].stackOffset -= 4 ; // gotta change this according to the TYPE
        }
        functions[currentFunction].symbolTable.push_back(st);
        st->parent = nullptr;
        //st1->parent = st;
    }else{
        st = nullptr;
        functions[currentFunction].symbolTable.push_back(st);
    }
    currentScope = st;
    //functions[currentFunction].symbolTable.push_back(st1);
    //currentScope = st1;
    visit(ctx->block());
    checkHasReturn();
    if (hasReturn == false) {
        std::cerr << "Erreur : Fonction '" << functionName << "' sans `return` !" << std::endl;
        exit(1);
    }
    hasReturn = false;
    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitMainFunction(ifccParser::MainFunctionContext *ctx) {
    Type functionReturnType = get_type(ctx->TYPE()->getText());
    std::string functionName = "main";
    currentFunction = functionName;
    functions[currentFunction].returnType = functionReturnType;
    //SymbolTable* st1 = new SymbolTable();
    functions[currentFunction].stackOffset = -4;
    SymbolTable* st = new SymbolTable();
    
    st = nullptr;
    functions[currentFunction].symbolTable.push_back(st);
    
    currentScope = st;
    //functions[currentFunction].symbolTable.push_back(st1);
    //currentScope = st1;
    visit(ctx->block());
    checkHasReturn();
    if (hasReturn == false) {
        std::cerr << "Erreur : Main '" << functionName << "' sans `return` !" << std::endl;
        exit(1);
    }
    hasReturn = false;
    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitFunctionCall(ifccParser::FunctionCallContext *ctx) {
    std::string functionName = ctx->VAR()->getText();
    if (functionName !="getchar" && functionName !="putchar" ){
        if (functions.find(functionName) == functions.end()) {
            std::cerr << "Erreur : Fonction '" << functionName << "' non déclarée !" << std::endl;
            exit(1);
        }
    
        int i =0;
        while (ctx->expr(i)) { 
            visit(ctx->expr(i));
            i++;
        }
        if(functions[functionName].symbolTable.at(0) != nullptr && functions[functionName].symbolTable.at(0)->table.size() != i){
            std::cerr << "Erreur : Fonction '" << functionName << "' prend "<< functions[functionName].symbolTable.size()<< " paramètres et non pas "<<i<< std::endl;
            exit(1);
        }
        //verifier si la fonction ne prend pas de parametres mais on en a mis
        if (functions[functionName].symbolTable.at(0) == nullptr && i != 0){
            std::cerr << "Erreur : Fonction '" << functionName << "' ne prend pas de paramètres. Vous avez passé " << i << " paramètres." << std::endl;
            exit(1);
        }
    
    }
    
    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitFunctionDec(ifccParser::FunctionDecContext *ctx) {
    std::string functionName = ctx->VAR()->getText();
    if (functions.find(functionName) == functions.end()) {
        // On ajoute la fonction à la map des fonctions déclarées
        Type functionReturnType = get_type(ctx->TYPE()->getText());
        functions[functionName].returnType = functionReturnType;
    } else {
        std::cerr << "Erreur : Fonction '" << functionName << "' déjà déclarée !" << std::endl;
        exit(1);
    }
    return 0;
}

void SymbolTableVisitor::checkUnusedVariables() {
    
    // Accéder à la table des symboles dans la portée actuelle
    if(currentScope==nullptr) return;
    const auto& symbolTable = currentScope->table;
    for (const auto& entry : symbolTable) {
        const auto& var = entry.second;
        int found = 0;
        if (functions[currentFunction].usedVariables.find(var.symbolOffset) == functions[currentFunction].usedVariables.end()) {
            std::cout << "# Avertissement : Variable '" << var.symbolName << "' déclarée mais jamais utilisée !" << std::endl;
            
        }
        
    }
}


void SymbolTableVisitor::checkHasReturn() {
    if (hasReturn==false) {
        std::cerr << "# Avertissement : Fonction sans `return` !" << std::endl;
    }else{
        std::cout << "# Fonction avec `return` !" << std::endl;}
}