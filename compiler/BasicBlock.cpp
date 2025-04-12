
#include <iostream>
#include <vector>

#include "BasicBlock.h"
#include "IRInstr.h"




// ---------- ASSEMBLEUR POUR BasicBlock ----------
BasicBlock::BasicBlock(CFG *cfg_, string entry_label)
	: cfg(cfg_), label(entry_label) {}

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params)
{
	instrs.push_back(new IRInstr(this, op, t, params));
}
void BasicBlock::add_IRInstrAtTop(IRInstr::Operation op, Type t, vector<string> params)
{
	instrs.insert(instrs.begin(), new IRInstr(this, op, t, params));
}
void BasicBlock::gen_asm(ostream &o)
{
	o << "_" << this->label << ":\n";
	for (auto instr : instrs)
	{
		instr->gen_asm(o);
	}
}

void BasicBlock::gen_asm_arm(ostream &o)
{
	
	if(this->label == "main"){
		o << "_main" << ":\n";
	}else{
		o << this->label << ":\n";
	}
	
	for (auto instr : instrs)
	{
		instr->gen_asm_arm(o);
	}
}