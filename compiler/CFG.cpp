#include "CFG.h"

std::string CFG::IR_reg_to_asm(std::string param) const {
	if (std::all_of(param.begin(), param.end(), [](char c) { return std::isdigit(c) || c == '-'; })) {
		int offset = std::stoi(param);
		return is_arm ? "[sp, #" + std::to_string(-offset) + "]" : std::to_string(offset) + "(%rbp)";
	}
	int offset = get_var_index(param);
	return is_arm ? "[sp, #" + std::to_string(-offset) + "]" : std::to_string(offset) + "(%rbp)";
}

int CFG::get_var_index(const std::string &name) const {
	SymbolTable *current_symbol_table = symbolTable.at(currentST_index);
	return current_symbol_table->get(name).symbolOffset;
}

Type CFG::get_var_type(const std::string &name) const {
	SymbolTable *current_symbol_table = symbolTable.at(currentST_index);
	return current_symbol_table->get(name).symbolType;
}

void CFG::gen_asm(std::ostream &o)
{
#ifdef __APPLE__
	o << ".globl _" << functionName << "\n";
	o << "_" << functionName << ":\n";
#else
	o << ".globl " << functionName << "\n";
	o << functionName << ":\n";
#endif

	stack_allocation = -nextFreeSymbolIndex;
	if (stack_allocation % 16 != 0)
		stack_allocation += (16 - (stack_allocation % 16));

	currentST_index = 1;
	for (auto *bb : bbs) {
		bb->gen_asm(o);
	}

	o << "\n";
}
