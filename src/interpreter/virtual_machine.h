#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include <vector>
#include <unordered_map>
#include <stack>
#include <fstream>
#include <string>

#include "instruction.h"

class VirtualMachine{
private:
    std::vector<Instruction> instructions;
    void loadInstructions(const char* bytecodeFileName);
public:
    VirtualMachine(const char* bytecodeFileName);
    void run();
};

#endif
