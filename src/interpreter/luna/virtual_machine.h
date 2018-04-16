#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include <vector>
#include <unordered_map>
#include <stack>
#include <fstream>
#include <string>

#include "macros.h"
#include "instruction.h"
#include "operand.h"

#define VM_CALCULATION(name, operation) void VirtualMachine::name(){\
    Operand op1 = stack.top(); stack.pop();\
    Operand op2 = stack.top(); stack.pop();\
    if(op1.getType() == OP_TYPE::DOUBLE || op2.getType() == OP_TYPE::DOUBLE){\
        double a = op1.getValue<double>();\
        double b = op2.getValue<double>();\
        double *result = new double;\
        *result = a operation b;\
        Operand *resultOp = new Operand(OP_TYPE::DOUBLE, (void *)result);\
        stack.push(*resultOp);\
    }else{\
        int a = op1.getValue<int>();\
        int b = op2.getValue<int>();\
        int *result = new int;\
        *result = a operation b;\
        Operand *resultOp = new Operand(OP_TYPE::INT, (void *)result);\
        stack.push(*resultOp);\
        curInstructionPos++;\
    }\
    return ;}

#define VM_COMPARISON(name, operation) void VirtualMachine::name(){\
    Operand op1 = stack.top(); stack.pop();\
    Operand op2 = stack.top(); stack.pop();\
    bool *result = new bool;\
    if(op1.getType() == OP_TYPE::DOUBLE || op2.getType() == OP_TYPE::DOUBLE){\
        double a = op1.getValue<double>();\
        double b = op2.getValue<double>();\
        *result = b operation a;\
    }else{\
        int a = op1.getValue<int>();\
        int b = op2.getValue<int>();\
        *result = b operation a;\
    }\
    Operand *resultOp = new Operand(OP_TYPE::BOOL, (void *)result);\
    stack.push(*resultOp);\
    curInstructionPos++;}

class VirtualMachine{
private:
    std::vector<Instruction> instructions;
    std::stack<Operand> stack;
    int curInstructionPos = 0;

    void loadInstructions(const char* bytecodeFileName);
    void runInstruction();
    void LDC(Instruction &ins);
    void HALT(Instruction &ins);
    void ADD();
    void SUB();
    void MUL();
    void DIV();
    void GT();
    void GE();
    void LT();
    void LE();
    void EQ();
    void NEQ();
    void PRT();
public:
    VirtualMachine(const char* bytecodeFileName);
    ~VirtualMachine();
    void run();
};

#endif
