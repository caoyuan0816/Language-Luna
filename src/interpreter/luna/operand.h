#ifndef OPERAND_H
#define OPERAND_H

#include <string>
#include <vector>
#include <iostream>

enum class OP_TYPE: unsigned int{
        BOOL, DOUBLE, INT
};

union OP_VALUE{
    int i;
    double d;
    bool b;
    uint8_t raw[sizeof(double)];
    OP_VALUE(): raw{} {}
};

class Operand{
public:
    OP_TYPE type;
    OP_VALUE value;
    std::string opStr;
    
    OP_TYPE checkOpType(std::string opStr);
    Operand();
    Operand(OP_TYPE type, OP_VALUE value);
    Operand(int commandIndex, std::vector<std::string> opStrList);
    Operand(const Operand &op);
    ~Operand();
    bool operator<(const Operand &op) const;
};

#endif
