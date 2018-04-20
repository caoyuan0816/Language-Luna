#include "operand.h"

Operand::Operand(){

}

Operand::Operand(int commandIndex, std::vector<std::string> opStrList){
    switch(commandIndex){
        case(1): {  //Const values
                    switch(checkOpType(opStrList[0])){
                        case(OP_TYPE::BOOL): {
                                     this->value = (void *) ::operator new(sizeof(bool));
                                     if(opStrList[0] == "true"){
                                         *(bool *)value = true;
                                     }else{
                                         *(bool *)value = false;
                                     }
                                     this->type = OP_TYPE::BOOL;
                                     break;
                                 }
                        case(OP_TYPE::DOUBLE): {
                                     this->value = (void *) ::operator new(sizeof(double));
                                     *(double *)value = std::stod(opStrList[0]);
                                     this->type = OP_TYPE::DOUBLE;
                                     break;
                                 }
                        case(OP_TYPE::INT): {
                                     this->value = (void *) ::operator new(sizeof(int));
                                     *(int *)value = std::stoi(opStrList[0]);
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

Operand::Operand(OP_TYPE type, void* value){
	this->type = type;
    switch(type){
        case(OP_TYPE::BOOL): {
            this->value = (void *) ::operator new(sizeof(bool));
            if((*(bool *)value)){
                *(bool *)this->value = true;
            }else{
                *(bool *)this->value = false;
            }
            break;
        }
        case(OP_TYPE::DOUBLE): {
            this->value = (void *) ::operator new(sizeof(double));
            *(double *)this->value = double(*(double *)value);
            break;
        }
        case(OP_TYPE::INT): {
            this->value = (void *) ::operator new(sizeof(int));
            *(int *)this->value = int(*(int *)value);
            break;
        }
        default: break;
    }
}

Operand::Operand(const Operand &op){
    this->type = type;
    switch(op.type){
        case(OP_TYPE::BOOL): {
            this->value = (void *) ::operator new(sizeof(bool));
            if((*(bool *)op.value)){
                *(bool *)this->value = true;
            }else{
                *(bool *)this->value = false;
            }
            break;
        }
        case(OP_TYPE::DOUBLE): {
            this->value = (void *) ::operator new(sizeof(double));
            *(double *)this->value = double(*(double *)op.value);
            break;
        }
        case(OP_TYPE::INT): {
            this->value = (void *) ::operator new(sizeof(int));
            *(int *)this->value = int(*(int *)op.value);
            break;
        }
        default: break;
    }
}

Operand::~Operand(){
    std::cout << "deleteing: " << this << " -> " << &value << " " << *(int *)value << std::endl;
    ::operator delete(value);
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
