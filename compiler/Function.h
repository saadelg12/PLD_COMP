#pragma once
#include <map>
#include <string>
#include <iostream>
#include "Type.h"

typedef struct {
    std::string symbolName;
    int symbolOffset;
    Type symbolType;
}Symbol;

