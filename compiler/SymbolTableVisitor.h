#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"

#include <map>
#include <set>
#include <string>
#include <iostream>
#include "SymbolTable.h"

class SymbolTableVisitor : public ifccBaseVisitor
{
private:
    std::map<std::string, std::vector<SymbolTable *>> *functionSymbolTablesPtr;
    std::map<std::string, int> *stackOffsetsPtr;

    std::string currentFunction;
    SymbolTable *currentScope = nullptr;
    std::vector<SymbolTable *> currentFunctionTables;
    int currentOffset = -4;

    std::map<std::string, std::string> functionsMap;            // Fonctions déclarées et leur type de retour
    std::map<std::string, std::set<std::string>> usedVariables; // Stocke les variables utilisées pour vérifier leur usage
    bool hasReturn = false;                                     // Vérifie si un `return` existe

public:
    SymbolTableVisitor(std::map<std::string, std::vector<SymbolTable *>> *fst,
                       std::map<std::string, int> *so)
        : functionSymbolTables(fst), stackOffsets(so) {}

    ~SymbolTableVisitor()
    {
        // Libérer toutes les tables de chaque fonction
        for (auto &pair : functionSymbolTables)
        {
            for (SymbolTable *st : pair.second)
            {
                delete st;
            }
            pair.second.clear(); // Vider le vecteur
        }

        functionSymbolTables.clear(); // Vider la map
        currentScope = nullptr;
    }

    virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;
    // virtual antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override;
    virtual antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override;
    virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override;
    virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx);
    virtual antlrcpp::Any visitFunctionDef(ifccParser::FunctionDefContext *ctx) override;
    virtual antlrcpp::Any visitFunctionCall(ifccParser::FunctionCallContext *ctx) override;
    virtual antlrcpp::Any visitFunctionDec(ifccParser::FunctionDecContext *ctx) override;

    // void checkUnusedVariables();  // Vérifie si une variable a été déclarée mais jamais utilisée
    void checkHasReturn();                                                                                             // Vérifie si une fonction a un `return`
    std::map<std::string, std::vector<SymbolTable *>> getFunctionSymbolTables() const { return functionSymbolTables; } // Retourne la map des tables de symboles
    std::map<std::string, int> getStackOffsets() const { return stackOffsets; }                                        // Retourne la map des offsets de la pile
};
