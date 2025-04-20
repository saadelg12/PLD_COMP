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

// Classe IRGenerator : génère le code intermédiaire (IR) à partir de l'arbre syntaxique
class IRGenerator : public ifccBaseVisitor {
public:
    CFG *cfg; // Pointeur vers le CFG (Control Flow Graph)

    // Constructeur : initialise le générateur IR avec un CFG donné
    IRGenerator(CFG *cfg_) : cfg(cfg_)
    {
        // Initialisation des blocs de base (commentée pour le moment)
        // BasicBlock *current_bb = new BasicBlock(cfg, "entry");
        // cfg->current_bb = current_bb;
        // cfg->add_bb(current_bb);
    }

    // Visite un nœud de type return_stmt et génère le code correspondant
    antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext* ctx) override;

    // Visite un nœud de type declaration et génère le code correspondant
    antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext* ctx) override;

    // Visite un nœud de type assignment et génère le code correspondant
    antlrcpp::Any visitAssignment(ifccParser::AssignmentContext* ctx) override;

    // Visite un nœud de type IdExpr (expression identifiant) et génère le code correspondant
    antlrcpp::Any visitIdExpr(ifccParser::IdExprContext* ctx) override;

    // Visite un nœud de type ConstExpr (expression constante) et génère le code correspondant
    antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext* ctx) override;

    // Visite un nœud de type AddSub (addition/soustraction) et génère le code correspondant
    antlrcpp::Any visitAddSub(ifccParser::AddSubContext* ctx) override;

    // Visite un nœud de type MulDiv (multiplication/division) et génère le code correspondant
    antlrcpp::Any visitMulDiv(ifccParser::MulDivContext* ctx) override;

    // Visite un nœud de type ParExpr (expression parenthésée) et génère le code correspondant
    antlrcpp::Any visitParExpr(ifccParser::ParExprContext* ctx) override;

    // Visite un nœud de type NegateExpr (expression négative) et génère le code correspondant
    antlrcpp::Any visitNegateExpr(ifccParser::NegateExprContext* ctx) override;

    // Visite un nœud de type NotExpr (expression NOT) et génère le code correspondant
    antlrcpp::Any visitNotExpr(ifccParser::NotExprContext* ctx) override;

    // Visite un nœud de type CmpExpr (expression de comparaison) et génère le code correspondant
    antlrcpp::Any visitCmpExpr(ifccParser::CmpExprContext* ctx) override;

    // Visite un nœud de type CharConstExpr (expression constante de type char) et génère le code correspondant
    antlrcpp::Any visitCharConstExpr(ifccParser::CharConstExprContext* ctx) override;

    // Visite un nœud de type BitwiseAndExpr (expression AND bit à bit) et génère le code correspondant
    antlrcpp::Any visitBitwiseAndExpr(ifccParser::BitwiseAndExprContext* ctx) override;

    // Visite un nœud de type BitwiseOrExpr (expression OR bit à bit) et génère le code correspondant
    antlrcpp::Any visitBitwiseOrExpr(ifccParser::BitwiseOrExprContext* ctx) override;

    // Visite un nœud de type BitwiseXorExpr (expression XOR bit à bit) et génère le code correspondant
    antlrcpp::Any visitBitwiseXorExpr(ifccParser::BitwiseXorExprContext* ctx) override;

    // Visite un nœud de type Block (bloc de code) et génère le code correspondant
    antlrcpp::Any visitBlock(ifccParser::BlockContext* ctx) override;

    // Visite un nœud de type If_stmt (instruction if) et génère le code correspondant
    antlrcpp::Any visitIf_stmt(ifccParser::If_stmtContext* ctx) override;

    // Visite un nœud de type While_stmt (instruction while) et génère le code correspondant
    antlrcpp::Any visitWhile_stmt(ifccParser::While_stmtContext *ctx);

    // Visite un nœud de type FunctionCall (appel de fonction) et génère le code correspondant
    antlrcpp::Any visitFunctionCall(ifccParser::FunctionCallContext* ctx) override;

    // Visite un nœud de type FunctionDef (définition de fonction) et génère le code correspondant
    antlrcpp::Any visitFunctionDef(ifccParser::FunctionDefContext* ctx) override;

    // Visite un nœud de type MainFunction (fonction main) et génère le code correspondant
    antlrcpp::Any visitMainFunction(ifccParser::MainFunctionContext* ctx) override;

private:
    Type lastExprType; // Type de la dernière expression visitée
};
