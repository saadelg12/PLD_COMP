#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"

#include <map>
#include <set>
#include <string>
#include <iostream>
#include "SymbolTable.h"
#include "Type.h"

class SymbolTableVisitor : public ifccBaseVisitor {
private:
    // Gestion par fonction
    std::map<std::string, std::vector<SymbolTable *>> functionSymbolTables;
    std::map<std::string, int> stackOffsets;
    std::map<std::string, Type> functionsMap;

    std::string currentFunction;
    SymbolTable *currentScope = nullptr;
    std::vector<SymbolTable *> currentFunctionTables;
    int currentOffset = -4;

    bool hasReturn = false;

public:
    SymbolTableVisitor();


    ~SymbolTableVisitor() {
        for (auto &entry : functionSymbolTables) {
            for (auto *table : entry.second) {
                delete table;
            }
        }
        functionSymbolTables.clear();
    }

    // Visiteurs
    virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;
    virtual antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override;
    virtual antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override;
    virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override;
    virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx) override;

    // Fonctions
    virtual antlrcpp::Any visitFunctionDef(ifccParser::FunctionDefContext *ctx) override;
    virtual antlrcpp::Any visitFunctionDec(ifccParser::FunctionDecContext *ctx) override;
    virtual antlrcpp::Any visitFunctionCall(ifccParser::FunctionCallContext *ctx) override;

    // Vérifications
    void checkUnusedVariables();
    void checkHasReturn();

    // Accès à l’état
    std::vector<SymbolTable *> getSymbolTables() const {
        return functionSymbolTables.at(currentFunction);
    }

    int getStackOffset() const {
        return stackOffsets.at(currentFunction);
    }

    const std::map<std::string, Type> &getFunctionsMap() const {
        return functionsMap;
    }
};
