#ifndef OPERAND_H
#define OPERAND_H

#include <string>
#include <vector>
#include <iostream>

enum class OP_TYPE: unsigned int{
        BOOL, DOUBLE, INT
    };

class Operand{
private:
    OP_TYPE type;
    void* value;
    OP_TYPE checkOpType(std::string opStr);
public:
    Operand(int commandIndex, std::vector<std::string> opStrList);
    Operand(OP_TYPE type, void* value);
    ~Operand();
    template <class T> T getValue();
    OP_TYPE getType();
};

template <class T>
T Operand::getValue(){
    return *(T *)value;
}
#endif
