#include "BasicBlock.h"
#include "CFG.h"

using namespace std;
// ---------- ASSEMBLEUR POUR BasicBlock ----------
BasicBlock::BasicBlock(CFG *cfg_, string entry_label)
	: cfg(cfg_), label(entry_label) {}

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params)
{
	instrs.push_back(new IRInstr(this, op, t, params));
}

void BasicBlock::gen_asm(ostream &o)
{
    o << this->label << ":" << endl;

    if (isFunctionEntry) {
        // Génère le prologue : sauvegarde base pointer et allocation stack
        o << "    push %rbp\n";
        o << "    mov %rsp, %rbp\n";
        o << "    sub $" << cfg->stack_allocation << ", %rsp\n";
    }

    for (auto instr : instrs)
    {
        if (cfg->is_arm)
            instr->gen_asm_arm(o);
        else
            instr->gen_asm(o);
    }

    if (instrs.empty() || instrs.back()->getOperation() != IRInstr::ret) {
        // Ajout automatique de l'épilogue si le retour n'a pas été explicite
        if (isFunctionEntry) {
            o << "    leave\n";
            o << "    ret\n";
        }
    }
}

