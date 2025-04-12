#pragma once

#include <string>
#include <vector>
using namespace std;

#include "Type.h"
class BasicBlock; // Pré-déclaration

// ---------- INSTRUCTION IR ----------
class IRInstr
{
public:
	enum Operation
	{
		ldconst,
		ldvar,
		copy,
		add,
		sub,
		mul,
		div,
		mod,
		neg,
		cmp_eq,
		cmp_expr,
		cmp_lt,
		cmp_le,
		cmp_ge,
		bitwise_and,
		bitwise_or,
		bitwise_xor,
		prologue,
		ret,
		cond_jump,
		assign_param,
		load_param_from_reg,
		call,
		jump
	};

	IRInstr(BasicBlock *bb_, Operation op, Type t, vector<string> params)
		: bb(bb_), op(op), t(t), params(params) {}

	Operation getOperation() const { return op; }

	void gen_asm(ostream &o);
	void gen_asm_arm(std::ostream &o);

private:
	BasicBlock *bb;
	Operation op;
	Type t;
	vector<string> params;

	string suffix_for_type(Type t)
	{
		switch (t)
		{
		case INT:
			return "l"; // long = 4 octets
		case CHAR:
			return "b"; // byte = 1 octet
		default:
			return "l"; // fallback = int
		}
	}
};