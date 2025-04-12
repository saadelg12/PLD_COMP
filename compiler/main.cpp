#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "generated/ifccLexer.h"
#include "generated/ifccParser.h"
#include "generated/ifccBaseVisitor.h"

#include "SymbolTableVisitor.h"
#include "IRGenerator.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv)
{
    cerr << ">>> ifcc démarre avec " << argn << " argument(s)" << endl;

    // Déclaration du flag pour le backend ARM
    bool use_arm = false;

    // Gestion des arguments
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
        cerr << ">>> Contenu du fichier lu :\n" << in.str() << endl;

        // Vérifie si --arm a été passé
        for (int i = 2; i < argn; ++i) {
            if (string(argv[i]) == "--arm") {
                use_arm = true;
                cerr << ">>> Compilation ciblée ARM activée" << endl;
            }
        }
    }
    else
    {
        cerr << "usage: ifcc path/to/file.c [--arm]" << endl;
        exit(1);
    }

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
    symbolTableVisitor.checkHasReturn();

    // IR + Assembleur
    CFG cfg(tree, symbolTableVisitor);
    cfg.is_arm = use_arm;

    IRGenerator irgen(&cfg);
    irgen.visit(tree);
    /*
    cerr << ">>> IR généré." << endl;

    cerr << ">>> Nombre de BasicBlocks : " << cfg.bbs.size() << endl;
    for (auto *bb : cfg.bbs)
    {
        cerr << "  - BasicBlock '" << bb->label << "' avec " << bb->instrs.size() << " instruction(s)" << endl;
        for (auto *instr : bb->instrs)
        {
            cerr << "    - Instruction : " << instr->getOperation() << endl;
        }
    }

    cerr << ">>> Génération de l'assembleur..." << endl;
    */
    cfg.gen_asm(std::cout);
    cerr << ">>> Fin de la génération assembleur." << endl;

    return 0;
}




