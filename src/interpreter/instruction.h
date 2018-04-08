#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <iostream>
#include <string>
#include <algorithm>

class Instruction{
private:
    static std::string const INSTRUCTION_LIST[];
    std::string command;
    int commandIndex;
public:
    Instruction(std::string command);
    int getCommandIndex();
};

#endif
