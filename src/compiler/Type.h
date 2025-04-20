
#ifndef TYPE_H
#define TYPE_H

// ---------- TYPES SUPPORTÉS ----------
enum Type
{
	INT,
	CHAR,
	DOUBLE,
	VOID
};


inline Type get_type(std::string type){
	if(type == "int") return INT;
	else if(type=="char") return CHAR;
	else if (type=="double") return DOUBLE;
	else return VOID;
}

inline int getTypeSize(Type type) {
    switch(type) {
        case INT: return 4;
        case CHAR: return 1;
        case DOUBLE: return 8;
        default: return 0;
    }
}
#endif

