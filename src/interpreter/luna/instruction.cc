#include "instruction.h"

//Size 19
std::string const Instruction::INSTRUCTION_LIST[] =
{"LDV", "LDC", "HALT", "CALL", "RET", "ADD", "SUB", "MUL", "DIV", "GT",
 "GE", "LT", "LE", "EQ", "NEQ", "JMP", "JZ", "ASN", "DUP"};

Instruction::Instruction(){
    
}

Instruction::~Instruction(){

}

Instruction::Instruction(int commandIndex, std::vector<std::string> opStrList){
    this->commandIndex = commandIndex;
    for(auto it = opStrList.begin(); it != opStrList.end(); it++){
        this->opStrList.push_back(*it);
    }
}

Instruction::Instruction(const Instruction &ins){
    commandIndex = ins.commandIndex;
    for(auto it = ins.opStrList.begin(); it != ins.opStrList.end(); it++){
        opStrList.push_back(*it);
    }
}

int Instruction::getCommandIndex(){
    return this->commandIndex;
}

std::vector<std::string> Instruction::getOpStrList(){
    return this->opStrList;
}
