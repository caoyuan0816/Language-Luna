#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <unordered_map>
#include <stack>
#include <fstream>
#include <string>
#include <functional>

#include "macros.h"
#include "instruction.h"
#include "operand.h"

#define FRAME_CALCULATION(name, operation) void Frame::name(){\
    Operand op1 = stack.top(); stack.pop();\
    Operand op2 = stack.top(); stack.pop();\
    if(op1.getType() == OP_TYPE::DOUBLE || op2.getType() == OP_TYPE::DOUBLE){\
        double a = op1.getValue<double>();\
        double b = op2.getValue<double>();\
        double *result = new double;\
        *result = b operation a;\
        Operand *resultOp = new Operand(OP_TYPE::DOUBLE, (void **)result);\
        stack.push(*resultOp);\
    }else{\
        int a = op1.getValue<int>();\
        int b = op2.getValue<int>();\
        int *result = new int;\
        *result = b operation a;\
        Operand *resultOp = new Operand(OP_TYPE::INT, (void *)result);\
        stack.push(*resultOp);\
    }\
    instructionPos++; return ;}

#define FRAME_COMPARISON(name, operation) void Frame::name(){\
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
    instructionPos++; return ;}

class Frame{
private:
    std::string frameName;
    std::vector<Instruction> instructions;
    std::stack<Operand> stack;
    std::unordered_map<std::string, Operand> variable_map;
    std::vector<Instruction>::iterator instructionPos;
    std::function<void(std::string, std::unordered_map<std::string, Operand> *)> vmRunFrameCallBack;
    std::function<void(Operand)> vmFrameReturnCallBack;

    void runInstruction(Instruction &curInstruction);
    void LDV(Instruction &ins);
    void LDC(Instruction &ins);
    void HALT(Instruction &ins);
    void CALL(Instruction &ins);
    void RET();
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
    void JMP(Instruction &ins);
    void JZ(Instruction &ins);
    void ASN(Instruction &ins);
    void DUP();
    void PRT(Instruction &ins);
public:
    Frame();
    Frame(std::string frameName,
        std::function<void(std::string, std::unordered_map<std::string, Operand> *)> vmRunFrameCallBack,
        std::function<void(Operand)> vmReturnCallBack);
    Frame(const Frame &frame);
    ~Frame();
    void pushInstruction(Instruction &ins);
    void pushOperand(Operand op);
    std::string getName();
    void setVariableMap(std::string key, Operand value);
    void run();
    bool operator < (const Frame & cmp) const;
};

#endif
