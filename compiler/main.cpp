#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "generated/ifccLexer.h"
#include "generated/ifccParser.h"
#include "generated/ifccBaseVisitor.h"

#include "SymbolTableVisitor.h"
#include "IRGenVisitor.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv)
{
    stringstream in;

    if (argn >= 2)
    {
        ifstream lecture(argv[1]);
        if (!lecture.good())
        {
            cerr << "error: cannot read file: " << argv[1] << endl;
            exit(1);
        }

        in << lecture.rdbuf();
    }
    else
    {
        cerr << "usage: ifcc path/to/file.c [--arm]" << endl;
        exit(1);
    }

    // Gestion du flag --arm
    bool use_arm = false;
    for (int i = 2; i < argn; ++i) {
        if (string(argv[i]) == "--arm") {
            use_arm = true;
            cerr << ">>> Compilation ciblée ARM activée" << endl;
        }
    }

    cerr << ">>> Contenu du fichier lu :\n" << in.str() << endl;

    ANTLRInputStream input(in.str());
    ifccLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    cerr << ">>> Lexing terminé. Nombre total de tokens : " << tokens.getNumberOfOnChannelTokens() << endl;

    ifccParser parser(&tokens);
    tree::ParseTree *tree = parser.axiom();

    if (parser.getNumberOfSyntaxErrors() != 0)
    {
        cerr << "error: syntax error during parsing" << endl;
        exit(1);
    }
    cerr << ">>> Parsing terminé sans erreur." << endl;

    // Symboles
    SymbolTableVisitor symbolTableVisitor;
    symbolTableVisitor.visit(tree);
    cerr << ">>> Visite de la table des symboles OK." << endl;

    symbolTableVisitor.checkUnusedVariables();

    // IR + Assembleur
    CFG placeholder_cfg("__placeholder__", nullptr, symbolTableVisitor);
    placeholder_cfg.is_arm = use_arm;
    
    IRGenVisitor irgen(&placeholder_cfg, &symbolTableVisitor);
    irgen.visit(tree);
    cerr << ">>> IR généré." << endl;

    // Section .rodata (constantes double globales)
    const auto& doubleConsts = irgen.getDoubleConstants();
    if (!doubleConsts.empty()) {
        cout << "\n    .section .rodata\n";
        for (const auto& pair : doubleConsts) {
            cout << pair.second << ":\n";
            cout << "    .double " << pair.first << "\n";
        }
        cout << "    .text\n";
    }

    // Génération assembleur pour chaque CFG
    for (const auto& [funcName, cfg] : irgen.getCFGMap()) {
        cfg->is_arm = use_arm;
        cerr << ">>> Fonction : " << funcName << " (" << cfg->bbs.size() << " blocs)\n";
        for (auto *bb : cfg->bbs)
        {
            cerr << "  - BasicBlock '" << bb->label << "' avec " << bb->instrs.size() << " instruction(s)" << endl;
        }

        cfg->gen_asm(std::cout);
    }

    cerr << ">>> Fin de la génération assembleur." << endl;
    return 0;
}
