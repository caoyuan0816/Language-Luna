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
    std::stack<void*> stack;
    int curInstructionPos = 0;

    void loadInstructions(const char* bytecodeFileName);
    void runInstruction();
    void LDC(Instruction ins);
    void ADD(Instruction ins);
public:
    VirtualMachine(const char* bytecodeFileName);
    ~VirtualMachine();
    void run();
};

#endif
