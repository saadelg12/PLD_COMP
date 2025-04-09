#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"

#include <map>
#include <set>
#include <string>
#include <iostream>
#include "SymbolTable.h" 

class SymbolTableVisitor : public ifccBaseVisitor {
private:
    SymbolTable * currentScope; 
    std::string currentFunction; // Nom de la fonction courante
    std::map<std::string, std::string> functions; // Nom de la fonction et son type
    std::map<std::string, std::vector<SymbolTable *>>  functionSymbolTables; // Liste des tables de symboles
    std::map<std::string, std::set<std::string>> usedVariables;   // Stocke les variables utilisées pour vérifier leur usage
    std::map<std::string, int> stackOffsets;   // Offset de la première variable (%rbp - 4)
    bool hasReturn = false;  // Vérifie si un `return` existe  
    

public:
    SymbolTableVisitor(): currentScope(nullptr){};

    ~SymbolTableVisitor() {
        // Libérer toutes les tables de chaque fonction
        for (auto& pair : functionSymbolTables) {
            for (SymbolTable* st : pair.second) {
                delete st;
            }
            pair.second.clear();  // Vider le vecteur
        }
    
        functionSymbolTables.clear();  // Vider la map
        currentScope = nullptr;
    }
    
    
    virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;
    //virtual antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override;
    virtual antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override;
    virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override;
    virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx);
    virtual antlrcpp::Any visitFunctionDef(ifccParser::FunctionContext *ctx) override;
    
    // void checkUnusedVariables();  // Vérifie si une variable a été déclarée mais jamais utilisée
    void checkHasReturn();  // Vérifie si une fonction a un `return`
    std::map<std::string, std::vector<SymbolTable *>>getFunctionSymbolTables()const { return functionSymbolTables; } // Retourne la map des tables de symboles
    std::map<std::string, int> getStackOffsets() const { return stackOffsets; } // Retourne la map des offsets de la pile
};
