#include "virtual_machine.h"

VirtualMachine::VirtualMachine(const char* bytecodeFileName){
    //Load instructions from file, store in vector instructions
    loadInstructions(bytecodeFileName);
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
            std::vector<std::string> opList;
            std::string command;
            std::size_t pos = 0;
            while((pos = line.find(" ")) != std::string::npos){
                std::string token = line.substr(0, pos);
                line.erase(0, pos + 1);
                if(isCommand){
                    command = token;
                    isCommand = false;
                }else{
                    opList.push_back(token);
                }
            }
            opList.push_back(line);
            //Build Instruction per line
            Instruction *ins = new Instruction(command, opList);
            instructions.push_back(*ins);
        }
    }else{
        std::cerr << "Cannot open bytecode file." << std::endl;
    }
    return ;
}

void VirtualMachine::run(){



    return ;
}


