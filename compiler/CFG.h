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
	CFG(const std::string& functionName)
		: currentFunction(functionName),
        symbolTable(),
        nextFreeSymbolIndex(),
        currentST_index(0),
        last_ST_index(0) {}

	void add_bb(BasicBlock *bb) { bbs.push_back(bb);}

	void gen_asm(ostream &o);
	void gen_asm_prologue(ostream &o);
	void gen_asm_epilogue(ostream &o);

	string IR_reg_to_asm(const string &reg) const
	{
		return to_string(get_var_index(reg)) + "(%rbp)";
	}

	int get_var_index(const string &name) const
	{
		//cout<< "looking for  "<<name<< " IN  "<<currentST_index<<endl;
		SymbolTable * current_symbol_table = symbolTable.at(currentST_index);
		int res = current_symbol_table->get(name).symbolOffset;
		return res;
	}
	Type get_var_type(const string &name) const
	{
		SymbolTable * current_symbol_table = symbolTable.at(currentST_index);
		return current_symbol_table->get(name).symbolType;
	}

	string create_new_tempvar(Type t)
	{
		string name = "!tmp" + to_string(-nextFreeSymbolIndex);
		Symbol s;
		s.symbolName = name;
		s.symbolOffset = nextFreeSymbolIndex;
		s.symbolType = t;
		symbolTable.at(currentST_index)->table[name] = s;
		//cout<< "creating "<<name<< " IN  "<<currentST_index<<endl;
		nextFreeSymbolIndex -= 4;
		
		return name;
	}
		
	int currentST_index;
	int last_ST_index;
	vector<BasicBlock *> bbs;
	vector<SymbolTable *> symbolTable;
	BasicBlock * current_bb;
	int nextFreeSymbolIndex;
	
private:
	void *ast;	
};