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
    std::vector<std::string> opStrList;
public:
    Instruction(std::string command, std::vector<std::string> opStrList);
    int getCommandIndex();
    std::vector<std::string> getOpStrList();
};

#endif
