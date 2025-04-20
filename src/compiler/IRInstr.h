#pragma once

#include <string>
#include <vector>
using namespace std;

#include "Type.h"
class BasicBlock; // Pré-déclaration de la classe BasicBlock

// ---------- INSTRUCTION IR ----------
class IRInstr
{
public:
	// Enumération des différentes opérations possibles pour une instruction IR
	enum Operation
	{
		ldconst,               // Charger une constante
		ldvar,                 // Charger une variable
		copy,                  // Copier une valeur
		add,                   // Addition
		sub,                   // Soustraction
		mul,                   // Multiplication
		div,                   // Division
		mod,                   // Modulo
		neg,                   // Négation
		cmp_eq,                // Comparaison d'égalité
		cmp_expr,              // Comparaison d'expression
		cmp_lt,                // Comparaison "moins que"
		cmp_le,                // Comparaison "moins ou égal"
		cmp_ge,                // Comparaison "plus ou égal"
		bitwise_and,           // Opération AND bit à bit
		bitwise_or,            // Opération OR bit à bit
		bitwise_xor,           // Opération XOR bit à bit
		prologue,              // Prologue d'une fonction
		int_to_double,         // Conversion d'un entier en double
		double_to_int,         // Conversion d'un double en entier
		ret,                   // Retour d'une fonction
		cond_jump,             // Saut conditionnel
		assign_param,          // Assignation d'un paramètre
		load_param_from_reg,   // Chargement d'un paramètre depuis un registre
		call,                  // Appel de fonction
		jump                   // Saut inconditionnel
	};

	// Constructeur de la classe IRInstr
	IRInstr(BasicBlock *bb_, Operation op, Type t, vector<string> params)
		: bb(bb_), op(op), t(t), params(params) {}

	// Retourne l'opération associée à l'instruction IR
	Operation getOperation() const { return op; }

	// Génère le code assembleur pour l'instruction IR (x86)
	void gen_asm(ostream &o);

	// Génère le code assembleur pour l'instruction IR (ARM)
	void gen_asm_arm(std::ostream &o);

private:
	BasicBlock *bb;           // Pointeur vers le bloc de base contenant l'instruction
	Operation op;             // Opération de l'instruction
	Type t;                   // Type de l'instruction
	vector<string> params;    // Paramètres de l'instruction

	// Retourne le suffixe correspondant au type pour le code assembleur
	string suffix_for_type(Type t)
	{
		switch (t)
		{
		case INT:
			return "l"; // long = 4 octets
		case CHAR:
			return "b"; // byte = 1 octet
		case DOUBLE:
			return "sd";// long = 8 octets
		default:
			return "l"; // fallback = int
		}
	}
};