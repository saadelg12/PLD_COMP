#include <iostream>
#include <vector>

#include "BasicBlock.h"
#include "IRInstr.h"

// ---------- ASSEMBLEUR POUR BasicBlock ----------

// Constructeur
// Initialise un BasicBlock avec un pointeur vers le CFG (Control Flow Graph) auquel il appartient
// et un label (étiquette) d'entrée pour identifier ce bloc.
BasicBlock::BasicBlock(CFG *cfg_, string entry_label)
	: cfg(cfg_), label(entry_label) {} 

// Ajoute une instruction IR (Intermediate Representation) à la fin du bloc
// @param op : L'opération IR à ajouter
// @param t : Le type des données manipulées par l'instruction
// @param params : Les paramètres nécessaires pour l'instruction
void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params)
{
	instrs.push_back(new IRInstr(this, op, t, params));
}

// Ajoute une instruction IR (Intermediate Representation) au début du bloc
// @param op : L'opération IR à ajouter
// @param t : Le type des données manipulées par l'instruction
// @param params : Les paramètres nécessaires pour l'instruction
void BasicBlock::add_IRInstrAtTop(IRInstr::Operation op, Type t, vector<string> params)
{
	instrs.insert(instrs.begin(), new IRInstr(this, op, t, params));
}

// Génère le code assembleur pour le bloc
// @param o : Flux de sortie où le code assembleur sera écrit
void BasicBlock::gen_asm(ostream &o)
{
	// Ajoute un underscore au label pour les systèmes macOS
	#ifdef __APPLE__
		o << "_" << this->label << ":\n";
	#endif

	// Ajoute le label du bloc
	o << this->label << ":\n";

	// Génère le code assembleur pour chaque instruction IR du bloc
	for (auto instr : instrs)
	{
		instr->gen_asm(o);
	}
}

// Génère le code assembleur ARM pour le bloc
// @param o : Flux de sortie où le code assembleur ARM sera écrit
void BasicBlock::gen_asm_arm(ostream &o)
{
	// Si le label est "main", ajoute un underscore pour respecter les conventions ARM
	if(this->label == "main"){
		o << "_main" << ":\n";
	}else{
		o << this->label << ":\n";
	}
	
	// Génère le code assembleur ARM pour chaque instruction IR du bloc
	for (auto instr : instrs)
	{
		instr->gen_asm_arm(o);
	}
}
