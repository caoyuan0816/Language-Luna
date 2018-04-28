#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include <vector>
#include <map>
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
    if(op1.type == OP_TYPE::DOUBLE && op2.type == OP_TYPE::DOUBLE){\
        OP_VALUE result;\
        result.d = op2.value.d operation op1.value.d;\
        Operand resultOp(OP_TYPE::DOUBLE, result);\
        stack.push(resultOp);\
    }else if(op1.type == OP_TYPE::DOUBLE && op2.type == OP_TYPE::INT){\
        OP_VALUE result;\
        result.d = (double)(op2.value.i operation op1.value.d);\
        Operand resultOp(OP_TYPE::DOUBLE, result);\
        stack.push(resultOp);\
    }else if(op1.type == OP_TYPE::INT && op2.type == OP_TYPE::DOUBLE){\
        OP_VALUE result;\
        result.d = (double)(op2.value.d operation op1.value.i);\
        Operand resultOp(OP_TYPE::DOUBLE, result);\
        stack.push(resultOp);\
    }else if(op1.type == OP_TYPE::INT && op2.type == OP_TYPE::INT){\
        OP_VALUE result;\
        result.i = op2.value.i operation op1.value.i;\
        Operand resultOp(OP_TYPE::INT, result);\
        stack.push(resultOp);\
    }else{\
        OP_VALUE result;\
        result.i = 0;\
        Operand resultOp(OP_TYPE::INT, result);\
        stack.push(resultOp);}\
    instructionPos++; return ;}

#define FRAME_COMPARISON(name, operation) void Frame::name(){\
    Operand op1 = stack.top(); stack.pop();\
    Operand op2 = stack.top(); stack.pop();\
    OP_VALUE result;\
    if(op1.type == OP_TYPE::DOUBLE && op2.type == OP_TYPE::DOUBLE){\
        result.b = op2.value.d operation op1.value.d;\
    }else{\
        result.b = op2.value.i operation op1.value.i;\
    }\
    Operand resultOp(OP_TYPE::BOOL, result);\
    stack.push(resultOp);\
    instructionPos++; return ;}

class Frame{
private:
    std::string frameName = "";
    std::vector<std::string> functionArgumentsName;
    std::vector<Instruction> instructions;
    std::stack<Operand> stack;
    std::map<std::string, Operand*> *variable_map = NULL;
    std::vector<Instruction>::iterator instructionPos;
    std::function<void(std::string, std::map<std::string, Operand*> *)> vmRunFrameCallBack;
    std::function<void(Operand&)> vmFrameReturnCallBack;
    std::function<void(void)> vmDeleteTopFrameCallBack;

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
public:
    Frame();
    Frame(std::string frameName, std::vector<std::string> functionArgumentsName,
        std::function<void(std::string, std::map<std::string, Operand*> *)> vmRunFrameCallBack,
        std::function<void(Operand&)> vmReturnCallBack,
        std::function<void(void)> vmDeleteTopFrameCallBack);
    Frame(const Frame &frame);
    ~Frame();
    void pushInstruction(Instruction &ins);
    void pushOperand(Operand &op);
    void run_print();
    std::string getName();
    void setVariableMap(std::map<std::string, Operand*> *callArgs);
    void run();
    bool operator < (const Frame & cmp) const;
};

#endif
