#include "BasicBlock.h"

#include "CFG.h"

// ---------- ASSEMBLEUR POUR CFG ----------
void CFG::gen_asm(std::ostream &o)
{
	if (is_arm)
	{

		for (auto st : functions)
		{
			string label = st.first;
			if (st.first == "main")
			{
				label = "main";
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

	// gen_asm_prologue(o);

	// currentST_index = 1;
	for (auto bb : bbs)
	{
		bb->gen_asm(o);
	}

	// gen_asm_epilogue(o);
}