#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include <vector>
#include <unordered_map>
#include <stack>
#include <fstream>
#include <string>
#include <sstream>

#include "instruction.h"
#include "operand.h"

class VirtualMachine{
private:
    std::vector<Instruction> instructions;
    std::stack<Operand> stack;
    int curInstructionPos = 0;

    void loadInstructions(const char* bytecodeFileName);
    void runInstruction();
    void LDC(Instruction &ins);
    void ADD(Instruction &ins);
    void SUB(Instruction &ins);
    void MUL(Instruction &ins);
    void DIV(Instruction &ins);
public:
    VirtualMachine(const char* bytecodeFileName);
    ~VirtualMachine();
    void run();
};

#endif
