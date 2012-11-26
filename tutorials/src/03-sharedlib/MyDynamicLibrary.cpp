#include <iostream>
#include "MyDynamicLibrary.h"


MyDynamicLibrary::MyDynamicLibrary()
{
	std::cout << "This is the constructor of MyDynamicLibrary" << std::endl;
}

MyDynamicLibrary::~MyDynamicLibrary()
{
	std::cout << "This is the DESTRUCTOR of MyDynamicLibrary" << std::endl;
}


int MyDynamicLibrary::fooMethod()
{
	return 10;
}



