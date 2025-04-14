#pragma once

#include <string>
#include <map>
#include <vector>
using namespace std;

#include "Type.h"
#include "SymbolTableVisitor.h"

class BasicBlock;

// ---------- GRAPHE DE CONTRÔLE ----------
class CFG
{
public:

	CFG(void *ast_, const SymbolTableVisitor &symtab)
		: ast(ast_),
		  functions(symtab.getFunctions()),
		  currentST_index(-1),
		  last_ST_index(-1) {}

	void add_bb(BasicBlock *bb) { bbs.push_back(bb);}

	void gen_asm(ostream &o);
	void gen_asm_prologue(ostream &o);
	void gen_asm_epilogue(ostream &o);

	map<string, Function> getFunctions() const { return functions; }

	// string IR_reg_to_asm(string param) const {
	// 	// Si c'est un offset explicite (ex: "-4"), on le traite directement
	// 	if (std::all_of(param.begin(), param.end(), [](char c) { return std::isdigit(c) || c == '-'; })) {
	// 		int offset = std::stoi(param);
	// 		if (is_arm)
	// 			return "[sp, #" + to_string(-offset) + "]"; // ARM utilise des offsets positifs
	// 		else
	// 			return to_string(offset) + "(%rbp)";        // X86 utilise des offsets négatifs
	// 	}
	
	// 	// Sinon, c'est un nom de variable ou de temporaire, on cherche son offset dans la symbol table
	// 	int offset = get_var_index(param);
	// 	if (is_arm)
	// 		return "[sp, #" + to_string(-offset) + "]";
	// 	else
	// 		return to_string(offset) + "(%rbp)";
	// }

	int get_var_index(const string &name) const
	{
		auto it = functions.find(currentFunction);
		//cout << "currentFunction "<<currentFunction << endl;
		SymbolTable * current_symbol_table = (it->second.symbolTable).at(currentST_index);
		
		
			
		//cout << "get_var_index: " << name << endl;
		
		int res = current_symbol_table->get(name).symbolOffset;
		//cout << "get_var_index: " << res << endl;
		return res;
	}
	Type get_var_type(const string &name) const
	{
		auto it = functions.find(currentFunction);
		SymbolTable * current_symbol_table = (it->second.symbolTable).at(currentST_index);
		return current_symbol_table->get(name).symbolType;
	}

	
		
	int currentST_index;
	int last_ST_index;
	string currentFunction;
	vector<BasicBlock *> bbs;
	map<string,Function> functions;
	BasicBlock * current_bb;
	bool is_arm = false;	  // false = x86, true = ARM
	int stack_allocation = 0; // Allocation pour décalage de sp
	int nb_getchar = 0;
	std::map<std::string, std::string> double_constants;
	int double_constant_counter = 0;
	
private:
	void *ast;	
};