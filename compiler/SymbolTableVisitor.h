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
    SymbolTable currentScope; 
    std::set<std::string> usedVariables;    // Stocke les variables utilisées pour vérifier leur usage
    int stackOffset = -4;  // Offset de la première variable (%rbp - 4)
    bool hasReturn = false;  // Vérifie si un `return` existe
    

public:
    virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;
    //virtual antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override;
    virtual antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override;
    virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override;
    
    void checkUnusedVariables();  // Vérifie si une variable a été déclarée mais jamais utilisée
    void checkHasReturn();  // Vérifie si une fonction a un `return`
    SymbolTable* getSymbolTable() { return &currentScope; } // Retourne la table des symboles actuelle
    int getStackOffset() { return stackOffset; } // Retourne l'offset
};

