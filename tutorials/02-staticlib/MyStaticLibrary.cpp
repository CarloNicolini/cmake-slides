#include <iostream>
#include "MyStaticLibrary.h"


MyStaticLibrary::MyStaticLibrary()
{
	std::cout << "This is the constructor of MyStaticLibrary" << std::endl;
}

MyStaticLibrary::~MyStaticLibrary()
{
	std::cout << "This is the DESTRUCTOR of MyStaticLibrary" << std::endl;
}


int MyStaticLibrary::fooMethod()
{
	return 10;
}



