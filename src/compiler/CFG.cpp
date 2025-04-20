#include "BasicBlock.h"

#include "CFG.h"

// ---------- ASSEMBLEUR POUR CFG ----------
// Cette méthode génère le code assembleur pour le CFG (Control Flow Graph).
// Elle produit le code en fonction de l'architecture cible (ARM ou X86).
// Les constantes double sont placées dans une section en lecture seule (.rodata).
// Les fonctions sont déclarées globales pour permettre leur utilisation externe.
// Les BasicBlocks (blocs de base) génèrent leur propre code assembleur selon l'architecture.
//
// Paramètres :
// - o : flux de sortie (std::ostream) où le code assembleur sera écrit.
void CFG::gen_asm(std::ostream &o)
{
	// Vérifie si la liste des constantes double n'est pas vide
	if (!double_constants.empty()) {
		// Déclare une section en lecture seule pour les données
		o << "\n    .section .rodata\n";
		for (const auto &pair : double_constants) {
			// Génère un label pour chaque constante double
			o << pair.second << ":\n";
			// Insère la valeur de la constante double
			o << "    .double " << pair.first << "\n";
		}
		// Retourne à la section texte
		o << "    .text\n";
	}
	
	// Vérifie si l'architecture cible est ARM
	if (is_arm)
	{
		// Génère les déclarations globales pour les fonctions
		for (auto st : functions)
		{
			string label = st.first;
			// Si la fonction est "main", adapte le label pour ARM
			if (st.first == "main")
			{
				label = "_main";
			}
			o << "    .globl " << label << "\n";
		}
		// Aligne les instructions sur une frontière de 4 octets
		o << "    .p2align 2\n";

		// Génère le code assembleur pour chaque BasicBlock en ARM
		for (auto bb : bbs)
		{
			bb->gen_asm_arm(o); // Ça imprime les labels et les instructions
		}

		return;
	}

	// Fallback pour l'architecture X86
#ifdef __APPLE__
	// Déclare le point d'entrée global pour macOS
	o << ".globl _main\n";
#else
	// Déclare le point d'entrée global pour les autres systèmes
	o << ".globl main\n";
	// o << "main:\n"; // Ligne commentée pour éviter un conflit potentiel
#endif

	// Génère le code assembleur pour chaque BasicBlock en X86
	for (auto bb : bbs)
	{
		bb->gen_asm(o);
	}
}