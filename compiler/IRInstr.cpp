#include "IRInstr.h"

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
		//o << "    mov" << s << " $" << params[1] << ", " << params[0] << "\n";
		o << "    mov" << s <<" " << params[0] << ", %eax\n";
		break;

	case copy:
		//o << "    mov" << s << " " << params[1] << ", %eax\n";
		o << "    mov" <<s << " %eax, " << params[0] << "\n";
		break;

	case add:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    add" << s << " " << params[1] << ", %eax\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case sub:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    sub" << s << " " << params[1] << ", %eax\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case mul:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    imul" << s << " " << params[1] << ", %eax\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case div:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    cltd\n";
		o << "    idiv" << s << " " << params[1] << "\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case mod:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    cltd\n";
		o << "    idiv" << s << " " << params[1] << "\n";
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
	o << "    cmp" << s << " "<<params[0]<<", %eax\n";
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
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    and" << s << " " << params[1] << ", %eax\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case bitwise_or:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    or" << s << " " << params[1] << ", %eax\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case bitwise_xor:
		o << "    mov" << s << " " << params[0] << ", %eax\n";
		o << "    xor" << s << " " << params[1] << ", %eax\n";
		//o << "    mov" << s << " %eax, " << params[0] << "\n";
		break;

	case ret:
	{
		// const string &src = params[0];
		// if (!src.empty() && src[0] == '$')
		// {
		// 	o << "    movl " << src << ", %eax\n";
		// }
		// else
		// {
		// 	o << "    mov" << s << " " << src << ", %eax\n";
		// 	if (s == "b")
		// 	{
		// 		o << "    movzbl %al, %eax\n"; // étend 8 bits → 32 bits
		// 	}
		// }
		o << "    leave\n";  
    	o << "    ret\n";       
		break;
	}
	case cond_jump:
	{
		//o << "    movl " << params[0] << ", %eax\n";  // Charge la valeur à tester
		o << "    test"<<s<<" %eax, %eax\n  ";
		o << "    jz "<<params[1]<<"\n";            //3. Saute si ZF=1 (valeur était 0)   ; 
		o << "    jnz "<<params[0]<<"\n";            //3. Saute si ZF=0 (valeur était différente de 0)   ; 
		break;
	}
	case jump:
	{
		o << "    jmp " << params[0] << "\n";
	}

	default:
		break;
	}
}
