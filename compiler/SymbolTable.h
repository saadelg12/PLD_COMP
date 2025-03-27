#pragma once
#include <map>
#include <string>
#include <iostream>

class SymbolTable {
public:
    SymbolTable* parent;  // Pointeur vers la table parent (nullptr si global)
    std::map<std::string, int> table;  // Stocke les variables du bloc courant

    // Constructeur par défaut
    SymbolTable() : parent(nullptr) {}
    
    SymbolTable(const SymbolTable& other) {
        // Copier les symboles de l'autre table (si tu as une structure comme un std::map, std::unordered_map, etc.)
        this->table = other.table;  // Cela suppose que `table` est une structure de données comme un `std::unordered_map` ou autre.
        
        // Copier d'autres membres si nécessaire
        this->parent = other.parent;  // Parent peut être partagé, ou tu peux aussi le définir différemment si nécessaire.
    }

    // Vérifie si une variable existe dans le scope courant
    bool contains(const std::string& varName) {
        return table.find(varName) != table.end();
    }

    // Insère une variable dans le scope courant
    void insert(const std::string& varName, int offset) {
        table[varName] = offset;
    }

    // Récupère la valeur d'une variable, en cherchant aussi dans les scopes parents
    int get(const std::string& varName) {
        if (table.find(varName) != table.end()) {
            return table[varName];  // Trouvé dans le scope actuel
        }
        if (parent) {
            return parent->get(varName);  // Rechercher dans le parent
        }
        return -1;  // Variable non trouvée
    }
};
