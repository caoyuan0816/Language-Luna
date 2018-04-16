#include "frame.h"

Frame::Frame(const char* bytecodeFileName){
    //Load instructions from file, store in vector instructions
    loadInstructions(bytecodeFileName);
}

Frame::~Frame(){
    for(auto it = instructions.begin(); it != instructions.end(); it++){
        //TODO
    }
}

void Frame::loadInstructions(const char* bytecodeFileName){
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
            if(isCommand){
                command = line;
            }else{
                opStrList.push_back(line);
            }
            //Build Instruction per line
            Instruction *ins = new Instruction(command, opStrList);
            this->instructions.push_back(*ins);
        }
    }else{
        std::string err("Cannot open bytecode file: ");
        err.append(bytecodeFileName);
        std::cout << err << std::endl;
        throw err.c_str();
    }
    return ;
}

//Will run instruction which pointed by curInstructionPos
void Frame::runInstruction(){
    Instruction curInstruction = instructions[curInstructionPos];
    switch(curInstruction.getCommandIndex()){
        case(0): break;
        case(1): LDC(curInstruction); break;
        case(2): HALT(curInstruction); break;
        case(3): break;
        case(4): break;
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
        case(15): break;
        case(16): break;
        case(17): ASN(curInstruction); break;
        case(18): DUP(); break;
        case(19): PRT(curInstruction); break;
        default: HALT(curInstruction); break;
    }
}

//Load Constant value to stack
void Frame::LDC(Instruction &ins){

    Operand *operand = new Operand(ins.getCommandIndex(), ins.getOpStrList());
    stack.push(*operand);

    curInstructionPos++;
    return ;
}

//Terminate program
void Frame::HALT(Instruction &ins){
    curInstructionPos = instructions.size();
    return ;
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

void Frame::ASN(Instruction &ins){

    variable_map[ins.getOpStrList()[0]] = stack.top();
    stack.pop();

    curInstructionPos++;
    return ;
}

void Frame::DUP(){

    Operand op = stack.top();
    Operand nop = *new Operand(op.type, op.value);
    stack.push(nop);

    curInstructionPos++;
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
    curInstructionPos++;
    return ;
}

void Frame::run(){

    while(curInstructionPos < instructions.size()){
        runInstruction();
    }

    return ;
}
