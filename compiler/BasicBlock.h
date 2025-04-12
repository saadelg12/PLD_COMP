#pragma once

#include <string>
#include <vector>
using namespace std;

#include "Type.h"
#include "CFG.h"
#include "IRInstr.h"


// ---------- BLOC DE BASE ----------
class BasicBlock
{
public:
	BasicBlock(CFG *cfg, string entry_label);
	void add_IRInstr(IRInstr::Operation op, Type t, vector<string> params);
	void add_IRInstrAtTop(IRInstr::Operation op, Type t, vector<string> params);
	void gen_asm(ostream &o);
	void gen_asm_arm(ostream &o);

	string label;
	CFG *cfg;
	vector<IRInstr *> instrs;
	BasicBlock *exit_true = nullptr;
	BasicBlock *exit_false = nullptr;
	BasicBlock *exit = nullptr;
	string test_var_name; 
};