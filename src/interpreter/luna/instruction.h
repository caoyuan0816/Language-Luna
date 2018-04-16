#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "macros.h"

class Instruction{
private:
    int commandIndex;
    std::vector<std::string> opStrList;
public:
	static std::string const INSTRUCTION_LIST[];
	Instruction();
    Instruction(int commandIndex, std::vector<std::string> opStrList);
    Instruction(const Instruction &ins);
    int getCommandIndex();
    std::vector<std::string> getOpStrList();
};

#endif
