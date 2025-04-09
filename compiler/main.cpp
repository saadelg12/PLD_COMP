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
  if (argn == 2)
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
    cerr << "usage: ifcc path/to/file.c" << endl;
    exit(1);
  }

  ANTLRInputStream input(in.str());

  ifccLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  tokens.fill();

  ifccParser parser(&tokens);
  tree::ParseTree *tree = parser.axiom();

  if (parser.getNumberOfSyntaxErrors() != 0)
  {
    cerr << "error: syntax error during parsing" << endl;
    exit(1);
  }

  SymbolTableVisitor symbolTableVisitor;
  symbolTableVisitor.visit(tree);
  // symbolTableVisitor.checkUnusedVariables();

  // Récupérer les maps
  auto functionSymbolTables = symbolTableVisitor.getFunctionSymbolTables();
  auto stackOffsets = symbolTableVisitor.getStackOffsets();

  auto functionSymbolTables = new std::map<std::string, std::vector<SymbolTable*>>();
  auto stackOffsets = new std::map<std::string, int>();
  
  // Génération de l’IR à partir de l’AST
  CFG cfg(tree, symbolTableVisitor);
  IRGenVisitor irgen(&cfg);
  irgen.visit(tree);

  // Génération du code assembleur depuis l’IR
  cfg.gen_asm(std::cout);

  return 0;
}
