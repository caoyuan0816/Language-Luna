#include "instruction.h"

//Size 19
std::string const Instruction::INSTRUCTION_LIST[] =
{"LDV", "LDC", "HALT", "CALL", "RET", "ADD", "SUB", "MUL", "DIV", "GT",
 "GE", "LT", "LE", "EQ", "NEQ", "JMP", "JZ", "ASN", "DUP"};

Instruction::Instruction(std::string command, std::vector<std::string> opList){
    this->command = command;
    this->opList = opList;
    //Finding commandIndex in INSTRUCTION_LIST
    auto res = std::find(INSTRUCTION_LIST, INSTRUCTION_LIST + 19, command);
    if(res != INSTRUCTION_LIST + 19){
        this->commandIndex = res - INSTRUCTION_LIST;
    }else{
        this->commandIndex = -1;
        std::cerr << "Error when initial instruction: " << command << std::endl;
    }
}

int Instruction::getCommandIndex(){
    return this->commandIndex;
}
