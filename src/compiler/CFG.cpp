#include "BasicBlock.h"

#include "CFG.h"

// ---------- ASSEMBLEUR POUR CFG ----------
void CFG::gen_asm(std::ostream &o)
{
	if (!double_constants.empty()) {
		o << "\n    .section .rodata\n";
		for (const auto &pair : double_constants) {
			o << pair.second << ":\n";
			o << "    .double " << pair.first << "\n";
		}
		o << "    .text\n";
	}
	
	if (is_arm)
	{

		for (auto st : functions)
		{
			string label = st.first;
			if (st.first == "main")
			{
				label = "_main";
			}
			o << "    .globl " << label << "\n";
		}
		o << "    .p2align 2\n";

		for (auto bb : bbs)
		{
			bb->gen_asm_arm(o); // Ça imprime les labels et les instructions
		}

		return;
	}

	// X86 fallback
#ifdef __APPLE__
	o << ".globl _main\n";
#else
	o << ".globl main\n";
	// o << "main:\n";
#endif

	for (auto bb : bbs)
	{
		bb->gen_asm(o);
	}
}