#include "SymbolTableVisitor.h"
#include "Type.h"

using namespace std;

SymbolTableVisitor::SymbolTableVisitor() {
    // Fonctions standard C
    functionsMap["getchar"] = INT;
    functionsMap["putchar"] = INT;
}

antlrcpp::Any SymbolTableVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
    std::string varName = ctx->VAR()->getText();
    Type varType = stringToType(ctx->TYPE()->getText());

    if (currentScope->contains(varName)) {
        std::cerr << "Erreur : Variable '" << varName << "' déjà déclarée dans ce scope !" << std::endl;
        exit(1);
    }

    int& offset = stackOffsets[currentFunction];
    currentScope->insert(varName, offset, varType);
    offset -= getTypeSize(varType);

    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitAssignment(ifccParser::AssignmentContext *ctx) {
    std::string varName = ctx->VAR()->getText();
    if (!currentScope->exists(varName)) {
        std::cerr << "Erreur : Variable '" << varName << "' utilisée sans être déclarée !" << std::endl;
        exit(1);
    }

    this->visit(ctx->expr());
    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitReturn_stmt(ifccParser::Return_stmtContext *ctx) {
    hasReturn = true;
    this->visit(ctx->expr());
    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) {
    std::string varName = ctx->VAR()->getText();

    if (!currentScope->exists(varName)) {
        std::cerr << "Erreur : Variable '" << varName << "' utilisée sans être déclarée !" << std::endl;
        exit(1);
    }

    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitBlock(ifccParser::BlockContext *ctx) {
    SymbolTable *newSymbolTable = new SymbolTable();
    newSymbolTable->parent = currentScope;
    currentScope = newSymbolTable;

    functionSymbolTables[currentFunction].push_back(currentScope);

    for (auto stmt : ctx->stmt()) {
        this->visit(stmt);
    }

    currentScope = currentScope->parent;
    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitFunctionDef(ifccParser::FunctionDefContext *ctx) {
    std::string functionName = ctx->VAR()->getText();
    currentFunction = functionName;

    Type returnType = stringToType(ctx->TYPE()->getText());
    functionsMap[currentFunction] = returnType;

    currentScope = new SymbolTable();
    currentFunctionTables.clear();
    currentFunctionTables.push_back(currentScope);

    currentOffset = -4;

    if (ctx->parameter_list()) {
        for (auto param : ctx->parameter_list()->parameter()) {
            std::string argName = param->VAR()->getText();
            Type argType = stringToType(param->TYPE()->getText());

            if (currentScope->contains(argName)) {
                std::cerr << "Erreur : Variable '" << argName << "' déjà déclarée dans ce scope !" << std::endl;
                exit(1);
            }

            currentScope->insert(argName, currentOffset, argType);
            currentOffset -= getTypeSize(argType);
        }
    }

    functionSymbolTables[currentFunction] = currentFunctionTables;
    stackOffsets[currentFunction] = currentOffset;

    hasReturn = false;
    visit(ctx->block());
    checkHasReturn();
    hasReturn = false;

    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitFunctionDec(ifccParser::FunctionDecContext *ctx) {
    std::string functionName = ctx->VAR()->getText();

    if (functionsMap.find(functionName) == functionsMap.end()) {
        Type returnType = stringToType(ctx->TYPE()->getText());
        functionsMap[functionName] = returnType;
    } else {
        std::cerr << "Erreur : Fonction '" << functionName << "' déjà déclarée !" << std::endl;
        exit(1);
    }

    return 0;
}

antlrcpp::Any SymbolTableVisitor::visitFunctionCall(ifccParser::FunctionCallContext *ctx) {
    std::string functionName = ctx->VAR()->getText();

    if (functionsMap.find(functionName) == functionsMap.end()) {
        std::cerr << "Erreur : Fonction '" << functionName << "' non déclarée !" << std::endl;
        exit(1);
    }

    return 0;
}

void SymbolTableVisitor::checkUnusedVariables() {
    const auto &tableList = functionSymbolTables[currentFunction];
    for (const auto &table : tableList) {
        for (const auto &[name, symbol] : table->symbols) {
            if (!symbol.used) {
                std::cerr << "Avertissement : variable '" << name << "' déclarée mais non utilisée." << std::endl;
            }
        }
    }
}

void SymbolTableVisitor::checkHasReturn() {
    if (functionsMap[currentFunction] != VOID && !hasReturn) {
        std::cerr << "Erreur : la fonction '" << currentFunction << "' ne retourne pas de valeur." << std::endl;
        exit(1);
    }
}
