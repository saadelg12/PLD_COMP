#pragma once
#include <map>
#include <string>
#include <iostream>
#include "Type.h"

struct Symbol {
    std::string symbolName;
    int symbolOffset;
    Type symbolType;
    bool used = false;  // Indique si la variable a été utilisée (par défaut non utilisée)
};

class SymbolTable {
public:
    SymbolTable* parent;  // Pointeur vers la table parent (nullptr si global)
    std::map<std::string, Symbol> symbols;  // Stocke les variables du bloc courant

    // Constructeur par défaut
    SymbolTable() : parent(nullptr) {}

    // Constructeur par copie
    SymbolTable(const SymbolTable& other) {
        this->symbols = other.symbols;
        this->parent = other.parent;
    }

    // Vérifie si une variable existe dans le scope courant
    bool contains(const std::string& varName) {
        return symbols.find(varName) != symbols.end();
    }

    // Vérifie si une variable est déclarée dans n'importe quel scope
    bool exists(const std::string& varName) {
        if (symbols.find(varName) != symbols.end()) {
            return true;
        }
        if (parent) {
            return parent->exists(varName);
        }
        return false;
    }

    // Insère une variable dans le scope courant
    void insert(const std::string& varName, int offset, Type type) {
        Symbol s;
        s.symbolName = varName;
        s.symbolOffset = offset;
        s.symbolType = type;
        s.used = false;
        symbols[varName] = s;
    }

    // Récupère la valeur d'une variable, en cherchant aussi dans les scopes parents
    Symbol get(const std::string& varName) {
        if (symbols.find(varName) != symbols.end()) {
            return symbols[varName];
        }
        if (parent) {
            return parent->get(varName);
        }
        Symbol s;
        s.symbolOffset = -1;
        return s;
    }
};
