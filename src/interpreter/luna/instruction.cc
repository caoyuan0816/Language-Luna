#include "instruction.h"

//Size 20
std::string const Instruction::INSTRUCTION_LIST[] =
{"LDV", "LDC", "HALT", "CALL", "RET", "ADD", "SUB", "MUL", "DIV", "GT",
 "GE", "LT", "LE", "EQ", "NEQ", "JMP", "JZ", "ASN", "DUP", "PRT"};

Instruction::Instruction(){
    
}

Instruction::Instruction(int commandIndex, std::vector<std::string> opStrList){
    this->commandIndex = commandIndex;
    this->opStrList = opStrList;
}

Instruction::Instruction(const Instruction &ins){
    commandIndex = ins.commandIndex;
    for(auto it = ins.opStrList.begin(); it != ins.opStrList.end(); it++){
        opStrList.push_back(std::string(*it));
    }
}

int Instruction::getCommandIndex(){
    return this->commandIndex;
}

std::vector<std::string> Instruction::getOpStrList(){
    return this->opStrList;
}
