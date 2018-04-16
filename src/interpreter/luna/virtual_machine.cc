#include "virtual_machine.h"

VirtualMachine::VirtualMachine(const char* bytecodeFileName){
	loadInstructions(bytecodeFileName);
}

VirtualMachine::~VirtualMachine(){

}

void VirtualMachine::loadInstructions(const char* bytecodeFileName){
    //Loading bytecode file to instructions list
    std::ifstream bytecodeFile;
    bytecodeFile.open(bytecodeFileName, std::ios::in);
    if(bytecodeFile.is_open()){
    	Frame* curFrame = NULL;
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
            auto res = std::find(Instruction::INSTRUCTION_LIST, Instruction::INSTRUCTION_LIST + 20, command);
            if(res != Instruction::INSTRUCTION_LIST + 20){
            	int commandIndex = res - Instruction::INSTRUCTION_LIST;
            	Instruction *ins = new Instruction(commandIndex, opStrList);
            	curFrame->pushInstruction(*ins);
            }else{//function name, create new
            	curFrame = new Frame(command.c_str(),
            		[this](std::string frameName, std::unordered_map<std::string, Operand> *callArgs){return this->runFrame(frameName, callArgs);},
            		[this](Operand op){return this->frameReturn(op);});
            	frameMap[curFrame->getName()] = curFrame;
            }
        }
    }else{
        std::string err("Cannot open bytecode file: ");
        err.append(bytecodeFileName);
        std::cout << err << std::endl;
        throw err.c_str();
    }
    return ;
}

void VirtualMachine::runFrame(std::string frameName, std::unordered_map<std::string, Operand> *callArgs){
	//Make a frame copy
	Frame *curFrame = new Frame();
	*curFrame = *frameMap[frameName];
	//std::cout << "runFrame" << " " << frameName << std::endl;
	if(callArgs != NULL){
		for(auto it = callArgs->begin(); it != callArgs->end(); it++){
			curFrame->setVariableMap(it->first, it->second);
		}
	}

	frameStack.push(curFrame);
	curFrame->run();
}

void VirtualMachine::frameReturn(Operand op){
	//std::cout << "returnFrame:" << " " << op.getValue<int>() << std::endl;
	frameStack.pop();
	frameStack.top()->pushOperand(op);
}

void VirtualMachine::run(){

	if(frameMap.find("main") != frameMap.end()){
		runFrame(std::string("main"), NULL);
	}else{
		std::string err("main function not found.");
        std::cout << err << std::endl;
        throw err.c_str();
	}
	

    return ;
}