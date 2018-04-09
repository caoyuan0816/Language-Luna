#include "virtual_machine.h"

VirtualMachine::VirtualMachine(const char* bytecodeFileName){
    //Load instructions from file, store in vector instructions
    loadInstructions(bytecodeFileName);
}

VirtualMachine::~VirtualMachine(){
    for(auto it = instructions.begin(); it != instructions.end(); it++){
        //TODO
    }
}

void VirtualMachine::loadInstructions(const char* bytecodeFileName){
    //Loading bytecode file to instructions list
    std::ifstream bytecodeFile;
    bytecodeFile.open(bytecodeFileName, std::ios::in);
    if(bytecodeFile.is_open()){
        std::string line;
        while(std::getline(bytecodeFile, line)){
            //Use token ' ' split line
            bool isCommand = true;
            std::vector<std::string> opStrList;
            std::string command;
            std::size_t pos = 0;
            while((pos = line.find(" ")) != std::string::npos){
                std::string token = line.substr(0, pos);
                line.erase(0, pos + 1);
                if(isCommand){
                    command = token;
                    isCommand = false;
                }else{
                    opStrList.push_back(token);
                }
            }
            opStrList.push_back(line);
            //Build Instruction per line
            Instruction *ins = new Instruction(command, opStrList);
            this->instructions.push_back(*ins);
        }
    }else{
        std::cerr << "Cannot open bytecode file." << std::endl;
    }
    return ;
}

//Will run instruction which pointed by curInstructionPos
void VirtualMachine::runInstruction(){
    Instruction curInstruction = instructions[curInstructionPos];
    switch(curInstruction.getCommandIndex()){
        case(0): break;
        case(1): LDC(curInstruction);break;
        case(2): break;
        case(3): break;
        case(4): break;
        case(5): ADD(curInstruction); break;
        case(6): break;
        case(7): break;
        case(8): break;
        case(9): break;
        case(10): break;
        case(11): break;
        case(12): break;
        case(13): break;
        case(14): break;
        case(15): break;
        case(16): break;
        case(17): break;
        case(18): break;
        case(19): break;
        default: break;
    }
}

//Load Constant value to stack
void VirtualMachine::LDC(Instruction &ins){

    Operand *operand = new Operand(ins.getCommandIndex(), ins.getOpStrList());
    stack.push(*operand);

    return ;
}

//Pop and add two top values in stack, and push result into stack
void VirtualMachine::ADD(Instruction &ins){

    Operand op1 = stack.top(); stack.pop();
    Operand op2 = stack.top(); stack.pop();

    if(op1.getType() == OP_TYPE::DOUBLE || op2.getType() == OP_TYPE::DOUBLE){
        double a = op1.getValue<double>();
        double b = op2.getValue<double>();
        double *result = new double;
        *result = a + b;
        Operand *resultOp = new Operand(OP_TYPE::DOUBLE, (void *)result);
        stack.push(*resultOp);
    }else{
        int a = op1.getValue<int>();
        int b = op2.getValue<int>();
        int *result = new int;
        Operand *resultOp = new Operand(OP_TYPE::DOUBLE, (void *)result);
        stack.push(*resultOp);
    }

    return ;
}

void VirtualMachine::run(){

    while(curInstructionPos < instructions.size()){
        runInstruction();
        curInstructionPos++;
    }

    Operand op = stack.top();
    if(op.getType() == OP_TYPE::INT){
        std::cout << op.getValue<int>() << std::endl;
    }else{
        std::cout << op.getValue<double>() << std::endl;
    }

    return ;
}
