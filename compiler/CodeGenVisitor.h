#pragma once


#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"


class CodeGenVisitor : public ifccBaseVisitor {
        private:
            std::map<std::string, int>* symbolTable;
        
        public:
            explicit CodeGenVisitor(std::map<std::string, int>* symTable) : symbolTable(symTable) {}
        
            virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;
            virtual antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override;
            virtual antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override;
            virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;
        
            virtual antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) override;
            virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override;
            virtual antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override;
            virtual antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) override;
            virtual antlrcpp::Any visitParenthesized(ifccParser::ParenthesizedContext *ctx) override;
        };
        
        

