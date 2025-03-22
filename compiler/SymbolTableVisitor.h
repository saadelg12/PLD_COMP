#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"

#include <map>
#include <set>
#include <string>
#include <iostream>

class SymbolTableVisitor : public ifccBaseVisitor {
private:
    std::map<std::string, int> symbolTable; // Associe une variable à son offset (%rbp - offset)
    std::set<std::string> usedVariables;    // Stocke les variables utilisées pour vérifier leur usage
    int stackOffset = -4;  // Offset de la première variable (%rbp - 4)
    bool hasReturn = false;  // Vérifie si un `return` existe
    

public:
    virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;
    // virtual antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override;
    virtual antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override;
    virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override;
    
    void checkUnusedVariables();  // Vérifie si une variable a été déclarée mais jamais utilisée
    void checkHasReturn();  // Vérifie si une fonction a un `return`
    std::map<std::string, int>* getSymbolTable() { return &symbolTable; } // Retourne la table des symboles
    int getStackOffset() { return stackOffset; } // Retourne l'offset
};

