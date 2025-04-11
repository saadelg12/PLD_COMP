#include "IRInstr.h"
#include "BasicBlock.h"
#include "CFG.h" 

using namespace std;

// ---------- ASSEMBLEUR POUR IRInstr ----------
void IRInstr::gen_asm(ostream &o)
{

	string s = suffix_for_type(t); // suffix for instruction based on type
	string dst;

	// if (op != ret)
	// {
	// 	dst = bb->cfg->IR_reg_to_asm(params[0]);
	// }

	switch (op)
	{
	case ldconst:
		if (t == DOUBLE) {
			o << "    movsd " << params[0] << "(%rip), %xmm0\n";
		} else {
			o << "    mov" << s << " $" << params[0] << ", %eax\n";
		}
		break;
	
	case ldvar:
		if (t == DOUBLE) {
			o << "    movsd " << params[0] << "(%rbp), %xmm0\n";
		} else {
			o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		}
		
		break;

	case copy:
		if (t == DOUBLE) {
			o << "    movsd %xmm0, " << params[0] << "(%rbp)\n";
		} else {
			o << "    mov" << s << " %eax, " << params[0] << "(%rbp)\n";
		}
		break;
	
	
	case add:
		if (t == DOUBLE) {
			o << "    movsd " << params[0] << "(%rbp), %xmm0\n";
			o << "    addsd " << params[1] << "(%rbp), %xmm0\n";
			// store result?
			// o << "    movsd %xmm0, " << params[0] << "\n";
		} else {
			o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
			o << "    add" << s << " " << params[1] << "(%rbp), %eax\n";
		}
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case sub:
		if (t == DOUBLE) {
			o << "    movsd " << params[0] << "(%rbp), %xmm0\n";
			o << "    subsd " << params[1] << "(%rbp), %xmm0\n";
			// store result?
			// o << "    movsd %xmm0, " << params[0] << "\n";
		} else {
			o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
			o << "    sub" << s << " " << params[1] << "(%rbp), %eax\n";
		}	
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case mul:
		if (t == DOUBLE) {
			o << "    movsd " << params[0] << "(%rbp), %xmm0\n";
			o << "    mulsd " << params[1] << "(%rbp), %xmm0\n";
			// store result?
			// o << "    movsd %xmm0, " << params[0] << "\n";
		} else {
			o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
			o << "    imul" << s << " " << params[1] << "(%rbp), %eax\n";
		}	
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case div:
		if (t == DOUBLE) {
			o << "    movsd " << params[0] << "(%rbp), %xmm0\n";
			o << "    divsd " << params[1] << "(%rbp), %xmm0\n";
			// store result?
			// o << "    movsd %xmm0, " << params[0] << "\n";
		} else {
			o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
			o << "    cltd\n";
			o << "    idiv" << s << " " << params[1] << "(%rbp)\n";
		}	
		
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case mod:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    cltd\n";
		o << "    idiv" << s << " " << params[1] << "(%rbp)\n";
		o << "    mov" << s << " %edx, %eax \n";
		break;
	case neg:
		o << "    neg" << s << " %eax\n";
		break;
	case cmp_eq:
		o << "    cmp" << s << " $0, %eax\n";
		o << "    mov" << s << " $0, %eax\n";
		o << "    sete %al\n";
		break;

	case cmp_expr:
		if (t == DOUBLE) {
			// params[0] = offset droit, params[1] = set instruction (seta, setbe, etc.)
	
			o << "    movsd " << params[0] << "(%rbp), %xmm1\n"; // droite
			o << "    ucomisd %xmm1, %xmm0\n";                    // compare xmm0 (gauche) à xmm1
	
			if (params[1] == "sete")        o << "    sete %al\n";
			else if (params[1] == "setne")  o << "    setne %al\n";
			else if (params[1] == "setl")   o << "    seta %al\n";   // a < b => unordered-safe
			else if (params[1] == "setle")  o << "    setae %al\n";  // a <= b
			else if (params[1] == "setg")   o << "    setb %al\n";   // a > b
			else if (params[1] == "setge")  o << "    setbe %al\n";  // a >= b
	
			o << "    movzbl %al, %eax\n"; // résultat dans eax
		} else {
			o << "    cmp" << s << " " << params[0] << "(%rbp), %eax\n";
			o << "    " << params[1] << " %al\n";
			o << "    movzbl %al, %eax\n";
		}
		break;
	
	case cmp_lt:
		if (t == CHAR)
		{
			o << "    movb " << params[1] << ", %al\n";
			o << "    cmpb " << params[2] << ", %al\n";
		}
		else
		{
			o << "    movl " << params[1] << ", %eax\n";
			o << "    cmpl " << params[2] << ", %eax\n";
		}
		o << "    setl %al\n";
		o << "    movzbl %al, %eax\n";
		o << "    movl %eax, " << params[0] << "\n";
		break;

	case cmp_le:
		if (t == CHAR)
		{
			o << "    movb " << params[1] << ", %al\n";
			o << "    cmpb " << params[2] << ", %al\n";
		}
		else
		{
			o << "    movl " << params[1] << ", %eax\n";
			o << "    cmpl " << params[2] << ", %eax\n";
		}
		o << "    setle %al\n";
		o << "    movzbl %al, %eax\n";
		o << "    movl %eax, " << params[0] << "\n";
		break;

	case cmp_ge:
		if (t == CHAR)
		{
			o << "    movb " << params[1] << ", %al\n";
			o << "    cmpb " << params[2] << ", %al\n";
		}
		else
		{
			o << "    movl " << params[1] << ", %eax\n";
			o << "    cmpl " << params[2] << ", %eax\n";
		}
		o << "    setge %al\n";
		o << "    movzbl %al, %eax\n";
		o << "    movl %eax, " << params[0] << "\n";
		break;

	case bitwise_and:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    and" << s << " " << params[1] << "(%rbp), %eax\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case bitwise_or:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    or" << s << " " << params[1] << "(%rbp), %eax\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case bitwise_xor:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    xor" << s << " " << params[1] << "(%rbp), %eax\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case int_to_double:
		//o << "    cvtsi2sd " << params[0] << "(%rbp), %xmm0\n";
		o << "    cvtsi2sd %eax, %xmm1\n";
		o << "    movsd %xmm1, " << params[0] << "(%rbp)\n";
		break;

	case double_to_int:
		//o << "    movsd " << params[0] << "(%rbp), %xmm0\n";
		o << "    cvttsd2si %xmm0, %eax\n";
		o << "    movl %eax, " << params[0] << "(%rbp)\n";
		break;

	case ret:
	{
		o << "    leave\n";
		o << "    ret\n";
		break;
	}
	case cond_jump:
	{
		o << "    test" << s << " %eax, %eax\n  ";
		o << "    jz " << params[1] << "\n";  // 3. Saute si ZF=1 (valeur était 0)   ;
		o << "    jnz " << params[0] << "\n"; // 3. Saute si ZF=0 (valeur était différente de 0)   ;
		break;
	}
	case jump:
	{
		o << "    jmp " << params[0] << "\n";
	}
	
	case call:
	{
		const std::string& funcName = params[0];

		if (funcName == "putchar") {
			std::string arg = params[1];
			o << "    movl " << arg << "(%rbp), %edi\n";
			o << "    call putchar\n";
		}
		else if (funcName == "getchar") {
			std::string dst = params[1];
			o << "    call getchar\n";
			o << "    movl %eax, " << dst << "(%rbp)\n";
		}
		else {
			// Fonction utilisateur
			const std::string& funcName = params[0];
		
			// Charger les arguments dans les registres standards (%rdi, %rsi, ...)
			std::vector<std::string> argRegs = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
			for (size_t i = 1; i < params.size(); ++i) {
				if (i - 1 < argRegs.size()) {
					o << "    movl " << params[i] << "(%rbp), " << argRegs[i - 1] << "\n";
				} else {
					o << "    # Warning: trop d'arguments pour call utilisateur\n";
				}
			}
			o << "    call " << funcName << "\n";
			// Résultat attendu dans %eax (ou %xmm0 si double)
		}	
		break;
	}


	default:
		break;
	}
}

void IRInstr::gen_asm_arm(std::ostream &o)
{
	string s = suffix_for_type(t);
	string dst;

	switch (op)
	{
	case ldconst:
		o << "    mov w0, #" << params[0] << "\n";
		break;

	case ldvar:
		o << "    ldr w0, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		break;

	case copy:
		o << "    str w0, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		break;

	case add:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    add w0, w1, w2\n";
		break;

	case sub:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    sub w0, w1, w2\n";
		break;

	case mul:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    mul w0, w1, w2\n";
		break;

	case div:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    sdiv w0, w1, w2\n";
		break;

	case mod:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    sdiv w3, w1, w2\n";
		o << "    msub w0, w3, w2, w1\n"; // mod = a - (a / b) * b
		break;

	case neg:
		o << "    neg w0, w0\n";
		break;

	case cmp_eq:
		o << "    cmp w0, #0\n";
		o << "    cset w0, eq\n";
		break;

	case cmp_expr:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    cmp w0, w1\n";
		if (params[1] == "sete")
			o << "    cset w0, eq\n";
		else if (params[1] == "setne")
			o << "    cset w0, ne\n";
		else if (params[1] == "setlt" || params[1] == "setl")
			o << "    cset w0, lt\n";
		else if (params[1] == "setle")
			o << "    cset w0, le\n";
		else if (params[1] == "setge")
			o << "    cset w0, ge\n";
		else if (params[1] == "setg")
			o << "    cset w0, gt\n";
		break;

	case cmp_lt:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    cmp w1, w2\n";
		o << "    cset w0, lt\n";
		o << "    str w0, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		break;

	case cmp_le:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    cmp w1, w2\n";
		o << "    cset w0, le\n";
		o << "    str w0, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		break;

	case cmp_ge:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[2]) << "\n";
		o << "    cmp w1, w2\n";
		o << "    cset w0, ge\n";
		o << "    str w0, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		break;

	case bitwise_and:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    and w0, w1, w2\n";
		break;

	case bitwise_or:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    orr w0, w1, w2\n";
		break;

	case bitwise_xor:
		o << "    ldr w1, " << bb->cfg->IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << bb->cfg->IR_reg_to_asm(params[1]) << "\n";
		o << "    eor w0, w1, w2\n";
		break;

	case ret:
		o << "    add sp, sp, #" << bb->cfg->stack_allocation << "\n";
		o << "    ret\n";
		break;

	case cond_jump:
		o << "    cmp w0, #0\n";
		o << "    b.eq " << params[1] << "\n";
		o << "    b " << params[0] << "\n";
		break;

	case jump:
		o << "    b " << params[0] << "\n";
		break;
	}
}
