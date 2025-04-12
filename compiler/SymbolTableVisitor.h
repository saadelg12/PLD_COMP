#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"

#include <map>
#include <set>
#include <string>
#include <iostream>
#include "SymbolTable.h" 

typedef struct {
    Type returnType;
    std::vector<SymbolTable *> symbolTable;
    std::set<int> usedVariables;
    int stackOffset;
}Function;

class SymbolTableVisitor : public ifccBaseVisitor {
private:
    SymbolTable * currentScope; 
    std::string currentFunction; // Nom de la fonction courante
    std::map<std::string, Function> functions; // Fonctions déclarées et leur type de retour
    bool hasReturn = false;  // Vérifie si un `return` existe  
    

public:
    SymbolTableVisitor(): currentScope(nullptr){};

    ~SymbolTableVisitor() {
        //Libérer toutes les tables de chaque fonction
        for (auto& pair : functions) {
            for (SymbolTable* st : pair.second.symbolTable) {
                delete st;
            }
            pair.second.symbolTable.clear();  // Vider le vecteur
        }
    
        functions.clear();  // Vider la map
        currentScope = nullptr;
    }
    
    
    virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;
    virtual antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override;
    virtual antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override;
    virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override;
    virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx);
    virtual antlrcpp::Any visitFunctionDef(ifccParser::FunctionDefContext *ctx) override;
    virtual antlrcpp::Any visitFunctionCall(ifccParser::FunctionCallContext *ctx) override;
    virtual antlrcpp::Any visitFunctionDec(ifccParser::FunctionDecContext *ctx) override;
    
    void checkUnusedVariables();  // Vérifie si une variable a été déclarée mais jamais utilisée
    void checkHasReturn();  // Vérifie si une fonction a un `return`
    std::map<std::string, Function> getFunctions()const { return functions; } 
    // std::map<std::string, std::vector<SymbolTable *>>getFunctionSymbolTables()const { return functionSymbolTables; } // Retourne la map des tables de symboles
    // std::map<std::string, int> getStackOffsets() const { return stackOffsets; } // Retourne la map des offsets de la pile
};
