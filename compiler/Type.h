
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

#endif

