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
  stringstream in;
  if (argn==2)
  {
     ifstream lecture(argv[1]);
     if( !lecture.good() )
     {
         cerr<<"error: cannot read file: " << argv[1] << endl ;
         exit(1);
     }
     in << lecture.rdbuf();
  }
  else
  {
      cerr << "usage: ifcc path/to/file.c" << endl ;
      exit(1);
  }
  
  ANTLRInputStream input(in.str());

  ifccLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  tokens.fill();

  ifccParser parser(&tokens);
  tree::ParseTree* tree = parser.axiom();

  if(parser.getNumberOfSyntaxErrors() != 0)
  {
      cerr << "error: syntax error during parsing" << endl;
      exit(1);
  }

  
  SymbolTableVisitor symbolTableVisitor;
  symbolTableVisitor.visit(tree);
  
  // symbolTableVisitor.checkUnusedVariables();
  // symbolTableVisitor.checkHasReturn();
  
  // CodeGenVisitor codeGenVisitor(symbolTableVisitor.getSymbolTable(), symbolTableVisitor.getStackOffset());
  // codeGenVisitor.visit(tree);

// Génération de l’IR à partir de l’AST
    CFG cfg(tree, symbolTableVisitor);
    map <std::string, Function> functions = cfg.getFunctions();
    // for (auto& pair : functions) {
    //     std::cout << "Function: " << pair.first << std::endl;
    //     std::cout << "Return Type: " << pair.second.returnType << std::endl;
    //     std::cout << "Stack Offset: " << pair.second.stackOffset << std::endl;
    //     std::cout << "Used Variables: ";
    //     for (int var : pair.second.usedVariables) {
    //         std::cout << var << " ";
    //     }
    //     for (SymbolTable* st : pair.second.symbolTable) {
    //         std::cout << "Symbol Table: " << std::endl;
    //         for (auto& symbol : st->table) {
    //             std::cout << "Name: " << symbol.second.symbolName << ", Offset: " << symbol.second.symbolOffset << ", Type: " << symbol.second.symbolType << std::endl;
    //         }
    //     }
    //     std::cout << std::endl;
    // }
    // auto it = functions.find("main");
		// SymbolTable * current_symbol_table = (it->second.symbolTable).at(1);
		
		// if(current_symbol_table != nullptr){
		// 	cout << "SIZE OF THE ST "<<current_symbol_table->table.size() << endl;
		// }
    IRGenerator irgen(&cfg);
    irgen.visit(tree);

    // Génération du code assembleur depuis l’IR
    cfg.gen_asm(std::cout);

  return 0;
}



