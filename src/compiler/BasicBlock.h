#pragma once

#include <string>
#include <vector>
using namespace std;

#include "Type.h"
#include "CFG.h"
#include "IRInstr.h"

// ---------- BLOC DE BASE ----------
class BasicBlock
{
public:
	// Constructeur de la classe BasicBlock
	// cfg : le CFG auquel appartient ce bloc de base
	// entry_label : le label d'entrée du bloc
	BasicBlock(CFG *cfg, string entry_label);

	// Ajoute une instruction IR à la fin du bloc
	// op : opération de l'instruction
	// t : type de l'instruction
	// params : paramètres de l'instruction
	void add_IRInstr(IRInstr::Operation op, Type t, vector<string> params);

	// Ajoute une instruction IR au début du bloc
	// op : opération de l'instruction
	// t : type de l'instruction
	// params : paramètres de l'instruction
	void add_IRInstrAtTop(IRInstr::Operation op, Type t, vector<string> params);

	// Génère le code assembleur pour ce bloc (x86)
	// o : flux de sortie pour écrire le code assembleur
	void gen_asm(ostream &o);

	// Génère le code assembleur pour ce bloc (ARM)
	// o : flux de sortie pour écrire le code assembleur
	void gen_asm_arm(ostream &o);

	// Label du bloc de base
	string label;

	// Pointeur vers le CFG auquel appartient ce bloc
	CFG *cfg;

	// Liste des instructions IR contenues dans ce bloc
	vector<IRInstr *> instrs;

	// Pointeur vers le bloc de sortie en cas de condition vraie
	BasicBlock *exit_true = nullptr;

	// Pointeur vers le bloc de sortie en cas de condition fausse
	BasicBlock *exit_false = nullptr;

	// Pointeur vers le bloc de sortie (utilisé si pas de condition)
	BasicBlock *exit = nullptr;

	// Nom de la variable utilisée pour les tests conditionnels
	string test_var_name; 
};