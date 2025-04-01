#include "functionVisitor.h"

antlrcpp::Any functionVisitor::visitFunction(ifccParser::FunctionContext *ctx)
{
    // Crée une nouvelle table des symboles pour la fonction
    SymbolTable *functionScope = new SymbolTable(currentScope, ctx->ID()->getText(), ctx->type()->getText());
    symbolTables.push_back(functionScope); // Ajoute la nouvelle table des symboles à la liste
    currentScope = functionScope; // Met à jour la portée actuelle
    return antlrcpp::Any();
}