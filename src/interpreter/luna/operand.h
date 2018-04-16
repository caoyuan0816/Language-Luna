#ifndef OPERAND_H
#define OPERAND_H

#include <string>
#include <vector>
#include <iostream>

enum class OP_TYPE: unsigned int{
        BOOL, DOUBLE, INT
    };

class Operand{
public:
    OP_TYPE type;
    void* value;
    OP_TYPE checkOpType(std::string opStr);
    Operand();
    Operand(int commandIndex, std::vector<std::string> opStrList);
    Operand(OP_TYPE type, void* value);
    ~Operand();
    template <class T> T getValue();
    OP_TYPE getType();
    bool operator==(const Operand &op) const;
};

template <class T>
T Operand::getValue(){
    return *(T *)value;
}

//Defining hash function of class Operand
namespace std{
    template <>
    struct hash<Operand>{
        std::size_t operator()(const Operand& op) const{
            return (std::hash<void *>()(op.value));
        }
    };
}

#endif
