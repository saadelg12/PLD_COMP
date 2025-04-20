
// Generated from ifcc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "ifccVisitor.h"


/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ifccBaseVisitor : public ifccVisitor {
public:

  virtual std::any visitAxiom(ifccParser::AxiomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProg(ifccParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMainFunction(ifccParser::MainFunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDef(ifccParser::FunctionDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDec(ifccParser::FunctionDecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameter_list(ifccParser::Parameter_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameter(ifccParser::ParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(ifccParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStmt(ifccParser::StmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(ifccParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(ifccParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(ifccParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_stmt(ifccParser::If_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhile_stmt(ifccParser::While_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitwiseAndExpr(ifccParser::BitwiseAndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstExpr(ifccParser::ConstExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdExpr(ifccParser::IdExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitwiseOrExpr(ifccParser::BitwiseOrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulDiv(ifccParser::MulDivContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddSub(ifccParser::AddSubContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCharConstExpr(ifccParser::CharConstExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNegateExpr(ifccParser::NegateExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCallExpr(ifccParser::FunctionCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParExpr(ifccParser::ParExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCmpExpr(ifccParser::CmpExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignementExpr(ifccParser::AssignementExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNotExpr(ifccParser::NotExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitwiseXorExpr(ifccParser::BitwiseXorExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

