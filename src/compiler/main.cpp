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
    // Affiche le nombre d'arguments passés au programme
    cerr << ">>> ifcc démarre avec " << argn << " argument(s)" << endl;

    // Déclaration du flag pour le backend ARM
    bool use_arm = false;

    // Gestion des arguments
    stringstream in;
    if (argn >= 2)
    {
        // Lecture du fichier source passé en argument
        ifstream lecture(argv[1]);
        if (!lecture.good())
        {
            // Affiche une erreur si le fichier ne peut pas être lu
            cerr << "error: cannot read file: " << argv[1] << endl;
            exit(1);
        }

        // Charge le contenu du fichier dans un flux
        in << lecture.rdbuf();
        cerr << ">>> Contenu du fichier lu :\n" << in.str() << endl;

        // Vérifie si l'option --arm a été passée en argument
        for (int i = 2; i < argn; ++i) {
            if (string(argv[i]) == "--arm") {
                use_arm = true;
                cerr << ">>> Compilation ciblée ARM activée" << endl;
            }
        }
    }
    else
    {
        // Affiche l'usage du programme si aucun fichier n'est passé
        cerr << "usage: ifcc path/to/file.c [--arm]" << endl;
        exit(1);
    }

    // Création d'un flux d'entrée ANTLR à partir du contenu du fichier
    ANTLRInputStream input(in.str());

    // Initialisation du lexer pour analyser les tokens
    ifccLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    // Affiche le nombre total de tokens analysés
    cerr << ">>> Lexing terminé. Nombre total de tokens : " << tokens.getNumberOfOnChannelTokens() << endl;

    // Initialisation du parser pour analyser la syntaxe
    ifccParser parser(&tokens);
    tree::ParseTree *tree = parser.axiom();

    // Vérifie s'il y a des erreurs de syntaxe
    if (parser.getNumberOfSyntaxErrors() != 0)
    {
        cerr << "error: syntax error during parsing" << endl;
        exit(1);
    }
    cerr << ">>> Parsing terminé sans erreur." << endl;

    // Création et visite de la table des symboles
    SymbolTableVisitor symbolTableVisitor;
    symbolTableVisitor.visit(tree);
    cerr << ">>> Visite de la table des symboles OK." << endl;

    // Vérifie les variables inutilisées et la présence d'un return
    symbolTableVisitor.checkUnusedVariables();
    symbolTableVisitor.checkHasReturn();

    // Génération de l'IR et de l'assembleur
    CFG cfg(tree, symbolTableVisitor);
    cfg.is_arm = use_arm;

    // Visite de l'arbre pour générer l'IR
    IRGenerator irgen(&cfg);
    irgen.visit(tree);

    /*
    // Affiche les informations sur les BasicBlocks et les instructions générées
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

    // Génération de l'assembleur
    cerr << ">>> Génération de l'assembleur..." << endl;
    */

    // Génère le code assembleur et l'écrit dans la sortie standard
    cfg.gen_asm(std::cout);
    cerr << ">>> Fin de la génération assembleur." << endl;

    return 0;
}
