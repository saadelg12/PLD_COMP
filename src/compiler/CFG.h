#pragma once

#include <string>
#include <map>
#include <vector>
using namespace std;

#include "Type.h"
#include "SymbolTableVisitor.h"

class BasicBlock;

// ---------- GRAPHE DE CONTRÔLE ----------
class CFG
{
public:

	// Constructeur de la classe CFG
	// ast_ : pointeur vers l'arbre syntaxique abstrait
	// symtab : visiteur de la table des symboles contenant les fonctions
	CFG(void *ast_, const SymbolTableVisitor &symtab)
		: ast(ast_),
		  functions(symtab.getFunctions()),
		  currentST_index(-1),
		  last_ST_index(-1) {}

	// Ajoute un bloc de base (BasicBlock) à la liste des blocs
	void add_bb(BasicBlock *bb) { bbs.push_back(bb);}

	// Génère le code assembleur pour le graphe de contrôle
	void gen_asm(ostream &o);

	// Génère le prologue en assembleur (initialisation de la pile, etc.)
	void gen_asm_prologue(ostream &o);

	// Génère l'épilogue en assembleur (restauration de la pile, etc.)
	void gen_asm_epilogue(ostream &o);

	// Retourne la map des fonctions définies dans le programme
	map<string, Function> getFunctions() const { return functions; }

	// Retourne l'index d'une variable dans la table des symboles courante
	// name : nom de la variable
	int get_var_index(const string &name) const
	{
		auto it = functions.find(currentFunction);
		// Récupère la table des symboles courante
		SymbolTable * current_symbol_table = (it->second.symbolTable).at(currentST_index);
		
		// Récupère l'offset de la variable dans la table des symboles
		int res = current_symbol_table->get(name).symbolOffset;
		return res;
	}

	// Retourne le type d'une variable dans la table des symboles courante
	// name : nom de la variable
	Type get_var_type(const string &name) const
	{
		auto it = functions.find(currentFunction);
		// Récupère la table des symboles courante
		SymbolTable * current_symbol_table = (it->second.symbolTable).at(currentST_index);
		return current_symbol_table->get(name).symbolType;
	}

	// Index de la table des symboles courante
	int currentST_index;

	// Dernier index de la table des symboles utilisé
	int last_ST_index;

	// Nom de la fonction courante
	string currentFunction;

	// Liste des blocs de base (BasicBlock) du graphe de contrôle
	vector<BasicBlock *> bbs;

	// Map des fonctions définies dans le programme
	map<string,Function> functions;

	// Pointeur vers le bloc de base courant
	BasicBlock * current_bb;

	// Indique si l'architecture cible est ARM (true) ou x86 (false)
	bool is_arm = false;

	// Allocation pour le décalage du pointeur de pile (sp)
	int stack_allocation = 0;

	// Compteur pour le nombre d'appels à getchar
	int nb_getchar = 0;

	// Map des constantes double utilisées dans le programme
	std::map<std::string, std::string> double_constants;

	// Compteur pour générer des noms uniques pour les constantes double
	int double_constant_counter = 0;
	
private:
	// Pointeur vers l'arbre syntaxique abstrait
	void *ast;	
};