#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "Type.h"
#include "SymbolTableVisitor.h"
#include "BasicBlock.h"

// ---------- GRAPHE DE CONTRÔLE ----------
class CFG
{
public:
	CFG(std::string functionName_, void* ast_, const SymbolTableVisitor &symtab)
		: functionName(functionName_),
		  ast(ast_),
		  symbolTable(symtab.getSymbolTables()),
		  nextFreeSymbolIndex(symtab.getStackOffset()),
		  currentST_index(0),
		  last_ST_index(0) {}

	void add_bb(BasicBlock *bb) { bbs.push_back(bb); }

	void gen_asm(std::ostream &o);

	std::string IR_reg_to_asm(std::string param) const;

	int get_var_index(const std::string &name) const;
	Type get_var_type(const std::string &name) const;

	std::string functionName;
	int currentST_index;
	int last_ST_index;
	std::vector<BasicBlock *> bbs;
	std::vector<SymbolTable *> symbolTable;
	BasicBlock *current_bb;
	int nextFreeSymbolIndex;

	bool is_arm = false;	  // false = x86, true = ARM
	int stack_allocation = 0; // Allocation pour décalage de sp

private:
	void *ast;
};
