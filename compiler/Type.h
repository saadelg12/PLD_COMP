#ifndef TYPE_H
#define TYPE_H

#include <string>

enum Type {
    INT,
    CHAR,
    DOUBLE,
    VOID
};

inline int getTypeSize(Type type) {
    switch(type) {
        case INT: return 4;
        case CHAR: return 1;
        case DOUBLE: return 8;
        default: return 0;
    }
}

inline std::string typeToString(Type type) {
    switch(type) {
        case INT: return "int";
        case CHAR: return "char";
        case DOUBLE: return "double";
        case VOID: return "void";
        default: return "unknown";
    }
}

inline Type stringToType(std::string type){
    if(type == "int") return INT;
    else if(type == "char") return CHAR;
    else if(type == "double") return DOUBLE;
    else return VOID;
}


inline int alignStackOffset(int offset, int align) {
    int remainder = (-offset) % align;
    if (remainder != 0) {
        offset -= (align - remainder);
    }
    return offset;
}

#endif
