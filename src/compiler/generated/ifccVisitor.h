
// Generated from ifcc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "ifccParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ifccParser.
 */
class  ifccVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ifccParser.
   */
    virtual std::any visitAxiom(ifccParser::AxiomContext *context) = 0;

    virtual std::any visitProg(ifccParser::ProgContext *context) = 0;

    virtual std::any visitMainFunction(ifccParser::MainFunctionContext *context) = 0;

    virtual std::any visitFunctionDef(ifccParser::FunctionDefContext *context) = 0;

    virtual std::any visitFunctionDec(ifccParser::FunctionDecContext *context) = 0;

    virtual std::any visitParameter_list(ifccParser::Parameter_listContext *context) = 0;

    virtual std::any visitParameter(ifccParser::ParameterContext *context) = 0;

    virtual std::any visitBlock(ifccParser::BlockContext *context) = 0;

    virtual std::any visitStmt(ifccParser::StmtContext *context) = 0;

    virtual std::any visitDeclaration(ifccParser::DeclarationContext *context) = 0;

    virtual std::any visitAssignment(ifccParser::AssignmentContext *context) = 0;

    virtual std::any visitReturn_stmt(ifccParser::Return_stmtContext *context) = 0;

    virtual std::any visitFunctionCall(ifccParser::FunctionCallContext *context) = 0;

    virtual std::any visitIf_stmt(ifccParser::If_stmtContext *context) = 0;

    virtual std::any visitWhile_stmt(ifccParser::While_stmtContext *context) = 0;

    virtual std::any visitBitwiseAndExpr(ifccParser::BitwiseAndExprContext *context) = 0;

    virtual std::any visitConstExpr(ifccParser::ConstExprContext *context) = 0;

    virtual std::any visitIdExpr(ifccParser::IdExprContext *context) = 0;

    virtual std::any visitBitwiseOrExpr(ifccParser::BitwiseOrExprContext *context) = 0;

    virtual std::any visitMulDiv(ifccParser::MulDivContext *context) = 0;

    virtual std::any visitAddSub(ifccParser::AddSubContext *context) = 0;

    virtual std::any visitCharConstExpr(ifccParser::CharConstExprContext *context) = 0;

    virtual std::any visitNegateExpr(ifccParser::NegateExprContext *context) = 0;

    virtual std::any visitFunctionCallExpr(ifccParser::FunctionCallExprContext *context) = 0;

    virtual std::any visitParExpr(ifccParser::ParExprContext *context) = 0;

    virtual std::any visitCmpExpr(ifccParser::CmpExprContext *context) = 0;

    virtual std::any visitAssignementExpr(ifccParser::AssignementExprContext *context) = 0;

    virtual std::any visitNotExpr(ifccParser::NotExprContext *context) = 0;

    virtual std::any visitBitwiseXorExpr(ifccParser::BitwiseXorExprContext *context) = 0;


};

