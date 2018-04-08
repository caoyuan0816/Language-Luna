#include <iostream>

#include "virtual_machine.h"
#include "instruction.h"

using namespace std;

int main(void){

    VirtualMachine vm;

    Instruction ins("DIV");
    cout << ins.getCommandIndex() << endl;

    return 0;
}
