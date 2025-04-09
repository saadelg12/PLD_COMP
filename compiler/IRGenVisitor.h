#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"


#include "CFG.h"
#include "SymbolTableVisitor.h"
#include "Type.h"
#include "IRInstr.h"
#include "BasicBlock.h"
#include "CFG.h"

#include <map>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class IRGenVisitor : public ifccBaseVisitor {
public:
    IRGenVisitor(CFG* cfg);

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
    antlrcpp::Any visitBlock(ifccParser::BlockContext* ctx) override;
    antlrcpp::Any visitIf_stmt(ifccParser::If_stmtContext* ctx) override;
    antlrcpp::Any visitFunctionCall(ifccParser::FunctionCallContext* ctx) override;
    antlrcpp::Any visitFunctionDef(ifccParser::FunctionDefContext* ctx) override;


private:
    std::map<std::string, CFG*>  cfgMap; // Map des CFGs pour chaque fonction
};
