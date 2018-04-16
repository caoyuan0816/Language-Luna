#include <iostream>

#include "macros.h"
#include "virtual_machine.h"

int main(int argc, char** argv){

    if(argc == 1){
        LOG("No byte-code file for interpreter!")
        LOG("Usage: ./luna bytecodeFIle.luo")
        return 1;
    }

    try{
    	VirtualMachine vm(argv[1]);
        vm.run();
    }catch(...){
    	std::cout << "Eror occured! " << std::endl;
    }
    
    return 0;
}
