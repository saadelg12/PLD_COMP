#include "IR.h"

#include <iostream>

using namespace std;

// ----------- IRInstr::gen_asm() --------------
void IRInstr::gen_asm(ostream &out) {
    string dest = bb->cfg->IR_reg_to_asm(params[0]);

    switch(op) {
        case ldconst:
            out << "    movl $" << params[1] << ", " << dest << "\n";
            break;

        case copy:
            out << "    movl " << bb->cfg->IR_reg_to_asm(params[1]) << ", " << dest << "\n";
            break;

        case add:
            out << "    movl " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
            out << "    addl " << bb->cfg->IR_reg_to_asm(params[2]) << ", %eax\n";
            out << "    movl %eax, " << dest << "\n";
            break;

        case sub:
            out << "    movl " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
            out << "    subl " << bb->cfg->IR_reg_to_asm(params[2]) << ", %eax\n";
            out << "    movl %eax, " << dest << "\n";
            break;

        case mul:
            out << "    movl " << bb->cfg->IR_reg_to_asm(params[1]) << ", %eax\n";
            out << "    imull " << bb->cfg->IR_reg_to_asm(params[2]) << ", %eax\n";
            out << "    movl %eax, " << dest << "\n";
            break;

        default:
            out << "    # [IRInstr] Operation not implemented: " << op << "\n";
            break;
    }
}

BasicBlock::BasicBlock(CFG* _cfg, string entry_label) : cfg(_cfg), label(entry_label) {}

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params) {
    instrs.push_back(new IRInstr(this, op, t, params));
}

void BasicBlock::gen_asm(ostream &out) {
    out << label << ":\n";

    for (auto instr : instrs) {
        instr->gen_asm(out);
    }

    // Ici on assume que tout se termine par return ou jump POUR L'INSTANT
}

CFG::CFG(DefFonction* ast) : ast(ast), nextFreeSymbolIndex(-4), nextBBnumber(0) {}

void CFG::add_bb(BasicBlock* bb) {
    bbs.push_back(bb);
}

string CFG::IR_reg_to_asm(string reg) {
    int offset = get_var_index(reg);
    return to_string(offset) + "(%rbp)";
}

int CFG::get_var_index(string name) {
    return SymbolIndex.at(name);
}

void CFG::add_to_symbol_table(string name, Type t) {
    SymbolType[name] = t;
    SymbolIndex[name] = nextFreeSymbolIndex;
    nextFreeSymbolIndex -= 4;
}

string CFG::create_new_tempvar(Type t) {
    string temp = "!tmp" + to_string(-nextFreeSymbolIndex);
    add_to_symbol_table(temp, t);
    return temp;
}

void CFG::gen_asm_prologue(ostream &out) {
    out << "    pushq %rbp\n";
    out << "    movq %rsp, %rbp\n";

    int stackSize = -nextFreeSymbolIndex;
    stackSize += (16 - (stackSize % 16)) % 16; // alignement
    out << "    subq $" << stackSize << ", %rsp\n";
}

void CFG::gen_asm_epilogue(ostream &out) {
    out << "    leave\n";
    out << "    ret\n";
}

void CFG::gen_asm(ostream &out) {
    #ifdef __APPLE__
    out << ".globl _main\n";
    out << "_main:\n";
    #else
    out << ".globl main\n";
    out << "main:\n";
    #endif

    gen_asm_prologue(out);

    for (auto bb : bbs) {
        bb->gen_asm(out);
    }

    gen_asm_epilogue(out);
}
