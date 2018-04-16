#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include <vector>
#include <stack>
#include <map>
#include <string>

#include "frame.h"
#include "instruction.h"
#include "operand.h"

//Singleton class
class VirtualMachine{
private:
	std::vector<Instruction> instructions;
	std::stack<Frame*> frameStack;
	std::map<std::string, Frame*> frameMap;
	void loadInstructions(const char* bytecodeFileName);
public:
	std::vector<Instruction>::iterator instructionPos;
	
	VirtualMachine(const char* bytecodeFileName);
	~VirtualMachine();
	void runFrame(std::string frameName, std::unordered_map<std::string, Operand> *callArgs);
	void frameReturn(Operand op);
	void run();
};

#endif