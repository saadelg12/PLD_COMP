#ifndef TYPE_H
#define TYPE_H

// ---------- TYPES SUPPORTÉS ----------
// Définition d'une énumération pour représenter les types supportés
enum Type
{
	INT,    // Type entier (4 octets)
	CHAR,   // Type caractère (1 octet)
	DOUBLE, // Type double précision (8 octets)
	VOID    // Type vide (aucune taille)
};

// Fonction utilitaire pour obtenir un type à partir d'une chaîne de caractères
inline Type get_type(std::string type){
	if(type == "int") return INT;          // Si la chaîne est "int", retourne INT
	else if(type=="char") return CHAR;    // Si la chaîne est "char", retourne CHAR
	else if (type=="double") return DOUBLE; // Si la chaîne est "double", retourne DOUBLE
	else return VOID;                     // Sinon, retourne VOID
}

// Fonction utilitaire pour obtenir la taille en octets d'un type donné
inline int getTypeSize(Type type) {
	switch(type) {
		case INT: return 4;    // Taille d'un entier : 4 octets
		case CHAR: return 1;   // Taille d'un caractère : 1 octet
		case DOUBLE: return 8; // Taille d'un double : 8 octets
		default: return 0;     // Taille par défaut : 0 octet
	}
}
#endif
