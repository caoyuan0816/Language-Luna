/**
*@file frame.cc
*@brief Design frame of assembly language 
*@version 1.0
*@author Yuan Cao
*@date 04/20/2018
*/
#include "frame.h"

Frame::Frame(){

}

Frame::~Frame(){
    if(variable_map != NULL){
        for(auto it = (*variable_map).begin(); it != (*variable_map).end(); it++){
            ::operator delete(it->second);
        }
        delete variable_map;
    }
}

Frame::Frame(std::string frameName, std::vector<std::string> functionArgumentsName,
        std::function<void(std::string, std::map<std::string, Operand*> *)> vmRunFrameCallBack,
        std::function<void(Operand&)> vmReturnCallBack,
        std::function<void(void)> vmDeleteTopFrameCallBack){
    this->frameName = frameName;
    this->vmRunFrameCallBack = vmRunFrameCallBack;
    this->vmFrameReturnCallBack = vmReturnCallBack;
    this->vmDeleteTopFrameCallBack = vmDeleteTopFrameCallBack;
    this->functionArgumentsName = functionArgumentsName;
}

Frame::Frame(const Frame &frame){
    frameName = frame.frameName;
    for(auto it = frame.instructions.begin(); it != frame.instructions.end(); it++){
        instructions.push_back(*it);
        std::cout << (instructions.end() - 1)->getCommandIndex() << std::endl;
    }
    instructionPos = instructions.begin();
}


/**
* \brief Will run instruction which pointed by curInstruction
*/
void Frame::runInstruction(Instruction &curInstruction){
    switch(curInstruction.getCommandIndex()){
        case(0): LDV(curInstruction); break;
        case(1): LDC(curInstruction); break;
        case(2): HALT(curInstruction); break;
        case(3): CALL(curInstruction); break;
        case(4): RET(); break;
        case(5): ADD(); break;
        case(6): SUB(); break;
        case(7): MUL(); break;
        case(8): DIV(); break;
        case(9): GT(); break;
        case(10): GE(); break;
        case(11): LT(); break;
        case(12): LE(); break;
        case(13): EQ(); break;
        case(14): NEQ(); break;
        case(15): JMP(curInstruction); break;
        case(16): JZ(curInstruction); break;
        case(17): ASN(curInstruction); break;
        case(18): DUP(); break;
        default: HALT(curInstruction); break;
    }
}

/**
* \brief Load variable value to stack
*/
void Frame::LDV(Instruction &ins){
    stack.push(*(*variable_map)[ins.getOpStrList()[0]]);
    instructionPos++;
}

/**
* \brief Load constant value to stack
*/
void Frame::LDC(Instruction &ins){

    Operand operand(ins.getCommandIndex(), ins.getOpStrList());
    stack.push(operand);

    instructionPos++;
    return ;
}

/**
* \brief Define terminate program instruction
*/
void Frame::HALT(Instruction &ins){
    exit(0);
}

/**
* \brief Define function call instruction
*/
void Frame::CALL(Instruction &ins){
    std::map<std::string, Operand*> *callArgs = new std::map<std::string, Operand*>();
    int argn = std::stoi(ins.getOpStrList()[1]);
    for(int i = 0; i < argn; i++){
        (*callArgs)[std::to_string(i)] = new Operand(stack.top());
        stack.pop();
    }
    // Run new frame by VM callback function
    vmRunFrameCallBack(ins.getOpStrList()[0], callArgs);

    if(ins.getOpStrList()[0] != "print"){
        vmDeleteTopFrameCallBack();
    }
    instructionPos++;
}

/**
* \brief Define function call and return instruction
*/  
void Frame::RET(){
    Operand op = stack.top();
    stack.pop();
    vmFrameReturnCallBack(op);
    instructionPos = instructions.end();
}

/**
* \brief Define operators
*/
FRAME_CALCULATION(ADD, +)
FRAME_CALCULATION(SUB, -)
FRAME_CALCULATION(MUL, *)
FRAME_CALCULATION(DIV, /)

FRAME_COMPARISON(GT, >)
FRAME_COMPARISON(GE, >=)
FRAME_COMPARISON(LT, <)
FRAME_COMPARISON(LE, <=)
FRAME_COMPARISON(EQ, ==)
FRAME_COMPARISON(NEQ, !=)

/**
* \brief Define jump instruction. Jump to the specified line of instrction.
*/ 
void Frame::JMP(Instruction &ins){
    int des = std::stoi(ins.getOpStrList()[0]);
    instructionPos = instructions.begin() + des;
    return ;
}

/**
* \brief Jump if zero
*/
void Frame::JZ(Instruction &ins){
    Operand op = stack.top();
    stack.pop();
    if(op.type != OP_TYPE::BOOL){
        std::string err("Type maching error!");
        std::cout << err << std::endl;
        throw err.c_str();
    }else{
        if(op.value.b){
            instructionPos++;
        }else{
            int des = std::stoi(ins.getOpStrList()[0]);
            instructionPos = instructions.begin() + des;
        }
    }
    return ;
}

/**
* \brief Define assignment statement.
*/
void Frame::ASN(Instruction &ins){
    if(variable_map == NULL){
        variable_map = new std::map<std::string, Operand*>();
    }
    (*variable_map)[ins.getOpStrList()[0]] =  new Operand(stack.top());
    stack.pop();

    instructionPos++;
    return ;
}

/**
* \brief Duplicate the top item on the stack
*/
void Frame::DUP(){

    stack.push(stack.top());

    instructionPos++;
    return ;
}

/**
* \brief Give the value in the bx register to ax register.
*/
void Frame::run_print(){

    for(int i = 0; i < variable_map->size(); i++){
        LOG_OPERAND((*((*variable_map)[std::to_string(i)])))
        std::cout << std::endl;
    }
    return ;
}

void Frame::pushInstruction(Instruction &ins){
    this->instructions.push_back(ins);
}

std::string Frame::getName(){
    return this->frameName;
}

void Frame::setVariableMap(std::map<std::string, Operand*> *callArgs){
    if(callArgs != NULL){
        if(frameName == "print"){
            variable_map = callArgs;
        }else{
            std::map<std::string, Operand*> *tmp = new std::map<std::string, Operand*>();
            for(auto it = callArgs->begin(); it != callArgs->end(); it++){
                (*tmp)[functionArgumentsName[std::stoi(it->first)]] = new Operand(it->second->type, it->second->value);
            }
            variable_map = tmp;

            // callArgs map now useless, delete it
            for(auto it = (*callArgs).begin(); it != (*callArgs).end(); it++){
                ::operator delete(it->second);
            }
            delete callArgs;
        }
    }
}

bool Frame::operator < (const Frame & cmp) const{
    return frameName < cmp.frameName;
}

void Frame::run(){
    instructionPos = instructions.begin();
    while(instructionPos != instructions.end()){

        #ifdef __LUNA__DEBUG
        RUN_AND_LOG_INSTRUCTION((*instructionPos));
        #endif
        #ifndef __LUNA__DEBUG
        runInstruction(*instructionPos);
        #endif
    }
}

void Frame::pushOperand(Operand &op){
    stack.push(op);
}
