#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"

#include "SymbolTableVisitor.h"
#include "Type.h"
#include "IRInstr.h"
#include "BasicBlock.h"
#include "CFG.h"

#include <map>
#include <vector>
#include <iostream>
#include <string>

class IRGenVisitor : public ifccBaseVisitor {
public:
    IRGenVisitor(CFG* cfg, SymbolTableVisitor* symtab);

    // Expressions
    antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext* ctx) override;
    antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext* ctx) override;
    antlrcpp::Any visitAssignment(ifccParser::AssignmentContext* ctx) override;
    antlrcpp::Any visitVarExpr(ifccParser::VarExprContext* ctx) override;
    antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext* ctx) override;
    antlrcpp::Any visitAddSub(ifccParser::AddSubContext* ctx) override;
    antlrcpp::Any visitMulDiv(ifccParser::MulDivContext* ctx) override;
    antlrcpp::Any visitParExpr(ifccParser::ParExprContext* ctx) override;
    antlrcpp::Any visitNegateExpr(ifccParser::NegateExprContext* ctx) override;
    antlrcpp::Any visitNotExpr(ifccParser::NotExprContext* ctx) override;
    antlrcpp::Any visitCmpExpr(ifccParser::CmpExprContext* ctx) override;
    antlrcpp::Any visitCharConstExpr(ifccParser::CharConstExprContext* ctx) override;
    antlrcpp::Any visitBitwiseAndExpr(ifccParser::BitwiseAndExprContext* ctx) override;
    antlrcpp::Any visitBitwiseOrExpr(ifccParser::BitwiseOrExprContext* ctx) override;
    antlrcpp::Any visitBitwiseXorExpr(ifccParser::BitwiseXorExprContext* ctx) override;

    // Contrôle de flux
    antlrcpp::Any visitBlock(ifccParser::BlockContext* ctx) override;
    antlrcpp::Any visitIf_stmt(ifccParser::If_stmtContext* ctx) override;
    antlrcpp::Any visitWhile_stmt(ifccParser::While_stmtContext *ctx) override;

    // Fonctions
    antlrcpp::Any visitFunctionCall(ifccParser::FunctionCallContext* ctx) override;
    antlrcpp::Any visitFunctionDef(ifccParser::FunctionDefContext* ctx) override;
    antlrcpp::Any visitFunctionDec(ifccParser::FunctionDecContext* ctx) override;

    const std::map<std::string, CFG*>& getCFGMap() const { return cfgMap; }

    // Constantes double globales (section .rodata)
    const std::map<std::string, std::string>& getDoubleConstants() const { return double_constants; }

private:
    CFG *cfg;
    Type lastExprType;
    std::map<std::string, CFG*> cfgMap;
    SymbolTableVisitor* symbolTableVisitor; // pointeur vers la symbol table

    std::map<std::string, std::string> double_constants;
    int double_constant_counter = 0;
};
