#include "operand.h"

Operand::Operand(){
    type = OP_TYPE::INT;
    value.d = 10.0;
    opStr="";
}

Operand::Operand(int commandIndex, std::vector<std::string> opStrList){
    switch(commandIndex){
        case(1): {  //Const values
            opStr = opStrList[0];
                    switch(checkOpType(opStrList[0])){
                        case(OP_TYPE::BOOL): {
                                     if(opStrList[0] == "true"){
                                        value.b = true;
                                     }else{
                                        value.b = false;
                                     }
                                     this->type = OP_TYPE::BOOL;
                                     break;
                                 }
                        case(OP_TYPE::DOUBLE): {
                                     value.d = std::stod(opStrList[0]);
                                     this->type = OP_TYPE::DOUBLE;
                                     break;
                                 }
                        case(OP_TYPE::INT): {
                                     value.i = std::stoi(opStrList[0]);
                                     this->type = OP_TYPE::INT;
                                     break;
                                 }
                        default: break;
                    }
                    break;
                 }
        default: break;
    }
}

Operand::Operand(OP_TYPE type, OP_VALUE value){
    this->type = type;
    this->value = value;
    switch(this->type){
        case(OP_TYPE::BOOL):{
            opStr = std::to_string(this->value.b);
        }
        case(OP_TYPE::INT):{
            opStr = std::to_string(this->value.i);
        }
        case(OP_TYPE::DOUBLE):{
            opStr = std::to_string(this->value.d);
        }
        default:break;
    }
}

Operand::Operand(const Operand &op){
    this->type = op.type;
    this->value = op.value;
    switch(this->type){
        case(OP_TYPE::BOOL):{
            opStr = std::to_string(this->value.b);
        }
        case(OP_TYPE::INT):{
            opStr = std::to_string(this->value.i);
        }
        case(OP_TYPE::DOUBLE):{
            opStr = std::to_string(this->value.d);
        }
        default:break;
    }
}

Operand::~Operand(){
    //std::cout << "deleteing: " << this << " -> " << &value << " " << *(int *)value << std::endl;
    //::operator delete(value);
}

OP_TYPE Operand::checkOpType(std::string opStr){
    if(opStr == "true" || opStr == "false"){
        return OP_TYPE::BOOL; // Bool
    }else if(opStr.find(".") != std::string::npos){
        return OP_TYPE::DOUBLE; // Double
    }else{
        return OP_TYPE::INT; // Int
    }
}

bool Operand::operator<(const Operand &otherOp) const{
    return opStr < otherOp.opStr;
}
