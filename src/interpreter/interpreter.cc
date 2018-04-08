#include <iostream>

#include "virtual_machine.h"

using namespace std;

int main(int argc, char** argv){

    if(argc == 1){
        cout << "No byte-code file for interpreter!" << endl;
        cout << "Usage: ./luna bytecodeFIle.luo" << endl;
        return 1;
    }

    VirtualMachine vm(argv[1]);

    return 0;
}
