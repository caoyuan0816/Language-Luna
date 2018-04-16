#ifndef LUNA_MACRO_H
#define LUNA_MACRO_H

//#define __LUNA__DEBUG

#define LOG(x) std::cout << x << std::endl;
#define LOGI(x) std::cout << x << " ";
#define LOGE(x) std::cerr << x << std::endl;

#define RUN_AND_LOG_INSTRUCTION(ins) std::string line;\
        std::getline(std::cin, line);\
        if(variable_map.find("0") != variable_map.end()){\
            std::cout <<  frameName << "(" << variable_map["0"].getValue<int>() << "): ";\
        }else{\
            std::cout <<  frameName << ": ";\
        }\
        std::cout << instructionPos-instructions.begin() << " ";\
		std::cout << Instruction::INSTRUCTION_LIST[ins.getCommandIndex()] << " ";\
		if(ins.getCommandIndex() == 3) std::cout << std::endl;\
		if(ins.getCommandIndex() == 19) std::cout << std::endl;\
		runInstruction(*instructionPos);\
        if(stack.size() != 0 && (instructionPos - 1)->getCommandIndex() != 3){\
            switch(stack.top().getType()){\
                case(OP_TYPE::BOOL): {\
                    if(stack.top().getValue<bool>()){\
                        std::cout << "true" << std::endl;\
                    }else{\
                        std::cout << "false" << std::endl;\
                    }break;\
                }\
                case(OP_TYPE::INT): std::cout << stack.top().getValue<int>() << std::endl; break;\
                case(OP_TYPE::DOUBLE): std::cout << stack.top().getValue<double>() << std::endl; break;\
                default: break;\
            }\
        }else if((instructionPos-1)->getCommandIndex() == 19){}\
         else if((instructionPos - 1)->getCommandIndex() != 3){\
            std::cout << std::endl;}

#endif
