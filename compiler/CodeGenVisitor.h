#pragma once


#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "SymbolTable.h"

class  CodeGenVisitor : public ifccBaseVisitor {                
        private:
                SymbolTable *currentScope; // Table des symboles
                int tempVarOffset;  // Offset pour les variables temporaires
                
	public:
        explicit CodeGenVisitor(SymbolTable* table, int offset) : tempVarOffset(offset), currentScope(table) {}

        

        virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override ;
        virtual antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override;
        virtual antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override;
        virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;
        
        
        virtual antlrcpp::Any visitParExpr(ifccParser::ParExprContext *ctx) override;
        virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override;
        virtual antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) override;
        virtual antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override;
        virtual antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) override;
        
        virtual antlrcpp::Any visitNotExpr(ifccParser::NotExprContext *ctx) override;
        virtual antlrcpp::Any visitNegateExpr(ifccParser::NegateExprContext *ctx) override;
        virtual antlrcpp::Any visitBitwiseExpr(ifccParser::BitwiseExprContext *ctx) override;

        virtual antlrcpp::Any visitCmpExpr(ifccParser::CmpExprContext *ctx) override;
        
        virtual antlrcpp::Any visitCharConstExpr(ifccParser::CharConstExprContext *ctx) override;

        








};

