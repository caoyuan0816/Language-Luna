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

Frame::Frame(std::string frameName,
        std::function<void(std::string, std::map<std::string, Operand*> *)> vmRunFrameCallBack,
        std::function<void(Operand&)> vmReturnCallBack,
        std::function<void(void)> vmDeleteTopFrameCallBack){
    this->frameName = frameName;
    this->vmRunFrameCallBack = vmRunFrameCallBack;
    this->vmFrameReturnCallBack = vmReturnCallBack;
    this->vmDeleteTopFrameCallBack = vmDeleteTopFrameCallBack;
}

Frame::Frame(const Frame &frame){
    frameName = frame.frameName;
    for(auto it = frame.instructions.begin(); it != frame.instructions.end(); it++){
        instructions.push_back(*it);
        std::cout << (instructions.end() - 1)->getCommandIndex() << std::endl;
    }
    instructionPos = instructions.begin();
}


//Will run instruction which pointed by curInstruction
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
        case(19): PRT(curInstruction); break;
        default: HALT(curInstruction); break;
    }
}

void Frame::LDV(Instruction &ins){
    stack.push(*(*variable_map)[ins.getOpStrList()[0]]);
    instructionPos++;
}

//Load Constant value to stack
void Frame::LDC(Instruction &ins){

    Operand operand(ins.getCommandIndex(), ins.getOpStrList());
    stack.push(operand);

    instructionPos++;
    return ;
}

//Terminate program
void Frame::HALT(Instruction &ins){
    exit(0);
}

void Frame::CALL(Instruction &ins){
    std::map<std::string, Operand*> *callArgs = new std::map<std::string, Operand*>();
    int argn = std::stoi(ins.getOpStrList()[1]);
    for(int i = argn-1; i >= 0; i--){
        //std::cout << "Before: " << &stack.top() <<  " -> " << &(stack.top().value) <<  " " << *(int *)stack.top().value << std::endl;
        (*callArgs)[std::to_string(i)] = new Operand(stack.top());
        //std::cout << "After insert: " << &(*callArgs)["0"] <<  " -> " << &((*callArgs)["0"].value) << " " << *(int *)(*callArgs)["0"].value << std::endl;
        stack.pop();
    }
    vmRunFrameCallBack(ins.getOpStrList()[0], callArgs);
    instructionPos++;
}
    
void Frame::RET(){
    Operand op = stack.top();
    stack.pop();
    vmFrameReturnCallBack(op);
    instructionPos = instructions.end();
}

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

void Frame::JMP(Instruction &ins){
    int des = std::stoi(ins.getOpStrList()[0]);
    instructionPos = instructions.begin() + des;
    return ;
}

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

void Frame::ASN(Instruction &ins){
    if(variable_map == NULL){
        variable_map = new std::map<std::string, Operand*>();
    }
    (*variable_map)[ins.getOpStrList()[0]] =  new Operand(stack.top());
    stack.pop();

    instructionPos++;
    return ;
}

void Frame::DUP(){

    stack.push(stack.top());

    instructionPos++;
    return ;
}

void Frame::PRT(Instruction &ins){

    Operand op;
    if(ins.getOpStrList().size() == 0){
        op = stack.top();
    }else{
        op = *(*variable_map)[ins.getOpStrList()[0]];
    }

    switch(op.type){
        case(OP_TYPE::INT):
            LOG(op.value.i)
            break;
        case(OP_TYPE::DOUBLE):
            LOG(op.value.d)
            break;
        case(OP_TYPE::BOOL):
            if(op.value.b){
                LOG("true")
            }else{
                LOG("false")
            }
            break;
        default: break;
    }
    instructionPos++;
    return ;
}

void Frame::pushInstruction(Instruction &ins){
    this->instructions.push_back(ins);
}

std::string Frame::getName(){
    return this->frameName;
}

void Frame::setVariableMap(std::map<std::string, Operand*> *callArgs){
    variable_map = callArgs;
}

bool Frame::operator < (const Frame & cmp) const{
    return frameName < cmp.frameName;
}

void Frame::run(){
    bool returnFlag = false;
    instructionPos = instructions.begin();
    while(instructionPos != instructions.end()){

        if((*instructionPos).getCommandIndex() == 3){
            returnFlag = true;
        }
        #ifdef __LUNA__DEBUG
        RUN_AND_LOG_INSTRUCTION((*instructionPos));
        #endif
        #ifndef __LUNA__DEBUG
        runInstruction(*instructionPos);
        #endif
        if(returnFlag){
            vmDeleteTopFrameCallBack(); 
            returnFlag = false;
        }
    }
}

void Frame::pushOperand(Operand &op){
    stack.push(op);
}