#ifndef LUNA_MACRO_H
#define LUNA_MACRO_H

//#define __LUNA__DEBUG

#define LOG(x) std::cout << x << std::endl;
#define LOGI(x) std::cout << x << " ";
#define LOGE(x) std::cerr << x << std::endl;

#define LOG_OPERAND(OP) switch(OP.type){\
                            case(OP_TYPE::INT):\
                                std::cout << OP.value.i;\
                                break;\
                            case(OP_TYPE::DOUBLE):\
                                std::cout << OP.value.d;\
                                break;\
                            case(OP_TYPE::BOOL):\
                                if(OP.value.b){\
                                    std::cout << "true";\
                                }else{\
                                    std::cout << "false";\
                                }\
                                break;\
                            default: break;}

#define RUN_AND_LOG_INSTRUCTION(ins) std::string line;\
        std::getline(std::cin, line);\
        std::cout << frameName << "(";\
        for(auto it = functionArgumentsName.begin(); it != functionArgumentsName.end(); it++){\
            LOG_OPERAND((*((*variable_map)[*it])))\
            if(it != functionArgumentsName.end() - 1){std::cout << ", ";}}\
        std::cout << ") ";\
        std::cout << instructionPos-instructions.begin() << " ";\
		std::cout << Instruction::INSTRUCTION_LIST[ins.getCommandIndex()] << " ";\
		if(ins.getCommandIndex() == 3) std::cout << std::endl;\
		if(ins.getCommandIndex() == 19) std::cout << std::endl;\
		runInstruction(ins);\
        if(instructionPos!=instructions.end()){\
            if(stack.size() != 0 && (instructionPos - 1)->getCommandIndex() != 3){\
                switch(stack.top().type){\
                    case(OP_TYPE::BOOL): {std::cout<<"bool ";\
                        if(stack.top().value.b){\
                            std::cout << "true" << std::endl;\
                        }else{\
                            std::cout << "false" << std::endl;\
                        }break;\
                    }\
                    case(OP_TYPE::INT): std::cout<<"int ";std::cout << stack.top().value.i << std::endl; break;\
                    case(OP_TYPE::DOUBLE): std::cout<<"double ";std::cout << stack.top().value.d << std::endl; break;\
                    default: break;\
                }\
            }else if((instructionPos - 1)->getCommandIndex() == 19){}\
             else if((instructionPos - 1)->getCommandIndex() != 3){\
                std::cout << std::endl;\
            }\
        }else{\
            std::cout << std::endl;}

#endif
