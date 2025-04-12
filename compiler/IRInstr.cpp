#include <iostream>
#include "IRInstr.h"
using namespace std;

// ---------- ASSEMBLEUR POUR IRInstr ----------

string IR_reg_to_asm(string param) {
	// Si c'est un offset explicite (ex: "-4"), on le traite directement
		int offset = std::stoi(param);
		return "[sp, #" + to_string(-offset) + "]"; // ARM utilise des offsets positifs
}
string get_register_for_param(string param){
	if (param == "0") return "%edi";
	else if (param == "1") return "%esi";
	else if (param == "2") return "%edx";
	else if (param == "3") return "%ecx";
	else if (param == "4") return "%r8d";
	else if (param == "5") return "%r9d";
	else return param; // cas de plus de 6 paramètres , pas encore traité
}

void IRInstr::gen_asm(ostream &o)
{
	
	string s = suffix_for_type(t); // suffix for instruction based on type

	switch (op)
	{
	case ldconst:
		o << "    mov" << s << " $" << params[0] << ", %eax\n";
		break;

	case ldvar:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		break;

	case copy:
		o << "    mov" << s << " %eax, " << params[0] << "(%rbp)\n";
		break;

	case add:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    add" << s << " " << params[1] << "(%rbp), %eax\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case sub:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    sub" << s << " " << params[1] << "(%rbp), %eax\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case mul:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    imul" << s << " " << params[1] << "(%rbp), %eax\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case div:
		o << "    mov" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    cltd\n";
		o << "    idiv" << s << " " << params[1] << "(%rbp)\n";
		// o << "    mov" << s << " %eax, " << params[0] << "\n";
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
		o << "    cmp" << s << " " << params[0] << "(%rbp), %eax\n";
		o << "    " << params[1] << " %al\n";
		o << "    movzbl %al, %eax\n";
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

	case ret:
	{
		// o << "    leave\n";
		// o << "    ret\n";
		std::cout << "    popq %rbp\n";         // restore %rbp from the stack
    	std::cout << "    ret\n";               // return to the caller
		break;
	}
	case prologue:
	{
		std::cout << "    pushq %rbp\n";        // save %rbp on the stack
    	std::cout << "    movq %rsp, %rbp\n";   // define %rbp for the current function
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
		break;
	}
	case assign_param:
	{
		std::string reg = get_register_for_param(params[0]);
		o << "    mov"<<s<<" %eax, "<< reg <<"\n";
		break;
	}
	case load_param_from_reg:
	{
		std::string reg = get_register_for_param(params[1]);
		o << "    mov" << s << " " << reg << ", " << params[0] << "(%rbp)\n";
		break;
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
			std::string arg = params[1];
			o << "    call getchar\n";
			o << "    movl %eax, " << arg << "(%rbp)\n";
		}
		else{
			o << "    call " << funcName << "\n";
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
		o << "    ldr w0, " << IR_reg_to_asm(params[0]) << "\n";
		break;

	case copy:
		o << "    str w0, " << IR_reg_to_asm(params[0]) << "\n";
		break;

	case add:
		o << "    ldr w1, " << IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << IR_reg_to_asm(params[1]) << "\n";
		o << "    add w0, w1, w2\n";
		break;

	case sub:
		o << "    ldr w1, " << IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << IR_reg_to_asm(params[1]) << "\n";
		o << "    sub w0, w1, w2\n";
		break;

	case mul:
		o << "    ldr w1, " << IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << IR_reg_to_asm(params[1]) << "\n";
		o << "    mul w0, w1, w2\n";
		break;

	case div:
		o << "    ldr w1, " << IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << IR_reg_to_asm(params[1]) << "\n";
		o << "    sdiv w0, w1, w2\n";
		break;

	case mod:
		o << "    ldr w1, " << IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << IR_reg_to_asm(params[1]) << "\n";
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
		o << "    ldr w1, " << IR_reg_to_asm(params[0]) << "\n";
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
		o << "    ldr w1, " << IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr w2, " << IR_reg_to_asm(params[2]) << "\n";
		o << "    cmp w1, w2\n";
		o << "    cset w0, lt\n";
		o << "    str w0, " << IR_reg_to_asm(params[0]) << "\n";
		break;

	case cmp_le:
		o << "    ldr w1, " << IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr w2, " << IR_reg_to_asm(params[2]) << "\n";
		o << "    cmp w1, w2\n";
		o << "    cset w0, le\n";
		o << "    str w0, " << IR_reg_to_asm(params[0]) << "\n";
		break;

	case cmp_ge:
		o << "    ldr w1, " << IR_reg_to_asm(params[1]) << "\n";
		o << "    ldr w2, " << IR_reg_to_asm(params[2]) << "\n";
		o << "    cmp w1, w2\n";
		o << "    cset w0, ge\n";
		o << "    str w0, " << IR_reg_to_asm(params[0]) << "\n";
		break;

	case bitwise_and:
		o << "    ldr w1, " << IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << IR_reg_to_asm(params[1]) << "\n";
		o << "    and w0, w1, w2\n";
		break;

	case bitwise_or:
		o << "    ldr w1, " << IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << IR_reg_to_asm(params[1]) << "\n";
		o << "    orr w0, w1, w2\n";
		break;

	case bitwise_xor:
		o << "    ldr w1, " << IR_reg_to_asm(params[0]) << "\n";
		o << "    ldr w2, " << IR_reg_to_asm(params[1]) << "\n";
		o << "    eor w0, w1, w2\n";
		break;

	case ret:
		o << "    add sp, sp, #" << params[0] << "\n"; // params[0] = stack allocation
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
