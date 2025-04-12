#include "BasicBlock.h"

#include "CFG.h"

// ---------- ASSEMBLEUR POUR CFG ----------
// void CFG::gen_asm_prologue(ostream &o)
// {
// 	o << "    pushq %rbp\n";
// 	o << "    movq %rsp, %rbp\n";

// 	int total = -nextFreeSymbolIndex;
// 	if (total % 16 != 0)
// 		total += (16 - (total % 16));
// 	o << "    subq $64, %rsp\n";
// }

// void CFG::gen_asm_epilogue(ostream &o)
// {
// 	o << "    leave\n";
// 	o << "    ret\n";
// }

// void CFG::gen_asm(ostream &o)
// {
// #ifdef __APPLE__
// 	o << ".globl _main\n";
// 	o << "_main:\n";
// #else
// 	o << ".globl main\n";
// 	o << "main:\n";
// #endif
// 	//gen_asm_prologue(o);
// 	//currentST_index = 1;
// 	for (auto bb : bbs) {
//     	bb->gen_asm(o);
// 	}
// 	//gen_asm_epilogue(o);
// }

void CFG::gen_asm(std::ostream &o)
{
	if (is_arm)
	{
		// o << "    .globl _main\n";
		// o << "    .p2align 2\n";
		// o << "_main:\n";

		// int total = -nextFreeSymbolIndex;
		// if (total % 16 != 0)
		// 	total += (16 - (total % 16));
		// stack_allocation = total;

		// o << "    sub sp, sp, #" << total << "\n";

		// currentST_index = 1;

		for (auto bb : bbs)
		{
			bb->gen_asm_arm(o); // Ça imprime les labels et les instructions
		}

		return;
	}

	// X86 fallback
#ifdef __APPLE__
	o << ".globl _main\n";
	o << "_main:\n";
#else
	o << ".globl main\n";
	//o << "main:\n";
#endif

	//gen_asm_prologue(o);

	//currentST_index = 1;
	for (auto bb : bbs)
	{
		bb->gen_asm(o);
	}

	// gen_asm_epilogue(o);
}