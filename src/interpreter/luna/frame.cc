#include "frame.h"

Frame::Frame(){

}

Frame::Frame(std::string frameName,
        std::function<void(std::string, std::unordered_map<std::string, Operand> *)> vmRunFrameCallBack,
        std::function<void(Operand)> vmReturnCallBack){
    this->frameName = frameName;
    this->vmRunFrameCallBack = vmRunFrameCallBack;
    this->vmFrameReturnCallBack = vmReturnCallBack;
}

Frame::Frame(const Frame &frame){
    frameName = frame.frameName;
    for(auto it = frame.instructions.begin(); it != frame.instructions.end(); it++){
        Instruction ins = *new Instruction();
        ins = *it;
        instructions.push_back(ins);
    }
}

Frame::~Frame(){
    for(auto it = instructions.begin(); it != instructions.end(); it++){
        //TODO
    }
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
    stack.push(variable_map[ins.getOpStrList()[0]]);
    instructionPos++;
}

//Load Constant value to stack
void Frame::LDC(Instruction &ins){

    Operand *operand = new Operand(ins.getCommandIndex(), ins.getOpStrList());
    stack.push(*operand);

    instructionPos++;
    return ;
}

//Terminate program
void Frame::HALT(Instruction &ins){
    exit(0);
}

void Frame::CALL(Instruction &ins){
    std::unordered_map<std::string, Operand> callArgs = *new std::unordered_map<std::string, Operand>();
    int argn = std::stoi(ins.getOpStrList()[1]);

    for(int i = argn-1; i >= 0; i--){
        callArgs[std::to_string(i)] = stack.top();
        stack.pop();
    }

    vmRunFrameCallBack(ins.getOpStrList()[0], &callArgs);
    instructionPos++;
}
    
void Frame::RET(){
    Operand op = stack.top();
    vmFrameReturnCallBack(op);
    instructionPos++;
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
    if(op.getType() != OP_TYPE::BOOL){
        std::string err("Type maching error!");
        std::cout << err << std::endl;
        throw err.c_str();
    }else{
        if(op.getValue<bool>()){
            instructionPos++;  
        }else{
            int des = std::stoi(ins.getOpStrList()[0]);
            instructionPos = instructions.begin() + des;
        }
    }
    return ;
}

void Frame::ASN(Instruction &ins){

    variable_map[ins.getOpStrList()[0]] = stack.top();
    stack.pop();

    instructionPos++;
    return ;
}

void Frame::DUP(){

    Operand op = stack.top();
    Operand nop = *new Operand(op.type, op.value);
    stack.push(nop);

    instructionPos++;
    return ;
}

void Frame::PRT(Instruction &ins){

    Operand op;
    if(ins.getOpStrList().size() == 0){
        op = stack.top();
    }else{
        op = variable_map[ins.getOpStrList()[0]];
    }

    switch(op.getType()){
        case(OP_TYPE::INT):
            LOG(op.getValue<int>())
            break;
        case(OP_TYPE::DOUBLE):
            LOG(op.getValue<double>())
            break;
        case(OP_TYPE::BOOL):
            if(op.getValue<bool>()){
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

void Frame::setVariableMap(std::string key, Operand value){
    variable_map[key] = value;
}

bool Frame::operator < (const Frame & cmp) const{
    return frameName < cmp.frameName;
}

void Frame::run(){
    instructionPos = instructions.begin();
    while(instructionPos != instructions.end()){
        //std::cout << frameName << " " << instructionPos->getCommandIndex() << std::endl;
        runInstruction(*instructionPos);
    }
}

void Frame::pushOperand(Operand op){
    stack.push(op);
}