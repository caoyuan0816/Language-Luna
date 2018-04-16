#include <iostream>

#include "macros.h"
#include "frame.h"

int main(int argc, char** argv){

    if(argc == 1){
        LOG("No byte-code file for interpreter!")
        LOG("Usage: ./luna bytecodeFIle.luo")
        return 1;
    }

    try{
    	Frame vmf(argv[1]);
    	vmf.run();
    }catch(...){
    	std::cout << "Eror occured! " << std::endl;
    }
    
    return 0;
}
