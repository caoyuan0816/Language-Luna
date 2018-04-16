#include "operand.h"

Operand::Operand(){

}

Operand::Operand(int commandIndex, std::vector<std::string> opStrList){
    switch(commandIndex){
        case(1): {  //Const values
                    switch(checkOpType(opStrList[0])){
                        case(OP_TYPE::BOOL): {
                                     bool* value = new bool;
                                     if(opStrList[0] == "true"){
                                         *value = true;
                                     }else{
                                         *value = false;
                                     }
                                     this->type = OP_TYPE::BOOL;
                                     this->value = (void *)value;
                                     break;
                                 }
                        case(OP_TYPE::DOUBLE): {
                                     double* value = new double;
                                     *value = std::stod(opStrList[0]);
                                     this->type = OP_TYPE::DOUBLE;
                                     this->value = (void *)value;
                                     break;
                                 }
                        case(OP_TYPE::INT): {
                                     int* value = new int;
                                     *value = std::stoi(opStrList[0]);
                                     this->type = OP_TYPE::INT;
                                     this->value = (void *)value;
                                     break;
                                 }
                        default: break;
                    }
                    break;
                 }
        default: break;
    }
}

Operand::Operand(OP_TYPE type, void* value){
	this->type = type;
	this->value = value;
}

Operand::~Operand(){
    //TODO
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

OP_TYPE Operand::getType(){
    return type;
}

bool Operand::operator==(const Operand &otherOp) const{
    value == otherOp.value;
}
