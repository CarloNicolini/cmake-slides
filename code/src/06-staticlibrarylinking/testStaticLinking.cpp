#include <iostream>
#include "MyStaticLibrary.h"

int main(int argc, char *argv[])

{
    MyStaticLibrary lib;
    
    std::cout << lib.fooMethod() << std::endl;

    return 0;
}
