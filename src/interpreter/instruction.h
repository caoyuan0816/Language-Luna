#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class Instruction{
private:
    static std::string const INSTRUCTION_LIST[];
    std::string command;
    int commandIndex;
    std::vector<std::string> opList;
public:
    Instruction(std::string command, std::vector<std::string> opList);
    int getCommandIndex();
    std::string getOp(int index);
};

#endif
