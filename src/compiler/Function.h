#pragma once
#include <map>
#include <string>
#include <iostream>
#include "Type.h"


// Structure représentant un symbole dans le compilateur.
// Un symbole est défini par son nom, son décalage et son type.
typedef struct {
    std::string symbolName; // Nom du symbole (identifiant unique).
    int symbolOffset;       // Décalage du symbole dans la mémoire ou le contexte.
    Type symbolType;        // Type du symbole (par exemple, entier, flottant, etc.).
}Symbol;

