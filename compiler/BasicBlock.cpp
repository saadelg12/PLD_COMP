#include "BasicBlock.h"


// ---------- ASSEMBLEUR POUR BasicBlock ----------
BasicBlock::BasicBlock(CFG *cfg_, string entry_label)
	: cfg(cfg_), label(entry_label) {}

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params)
{
	instrs.push_back(new IRInstr(this, op, t, params));
}

void BasicBlock::gen_asm(ostream &o)
{
	o << this->label << ":\n";
	for (auto instr : instrs)
	{
		instr->gen_asm(o);
	}
}