#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"


#include "generated/ifccParser.h"
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

class IRGenerator : public ifccBaseVisitor {
public:
    CFG *cfg;

    IRGenerator(CFG *cfg_) : cfg(cfg_)
    {
        // BasicBlock *current_bb = new BasicBlock(cfg, "entry");
        // cfg->current_bb = current_bb;
        // cfg->add_bb(current_bb);
    }

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
    antlrcpp::Any visitWhile_stmt(ifccParser::While_stmtContext *ctx);
    antlrcpp::Any visitFunctionCall(ifccParser::FunctionCallContext* ctx) override;
    antlrcpp::Any visitFunctionDef(ifccParser::FunctionDefContext* ctx) override;


private:

};
