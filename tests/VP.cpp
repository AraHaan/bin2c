/*
	VP.cpp
*/

#ifdef _WIN32
#define _HAS_EXCRPTIONS 0
#endif
#include <string>
#include <iostream>
#include <fstream>
#include "VP.hpp"

int main()
{
	std::string created_msg = "Created ";
	created_msg += IMAGE_VP_NAME;
	created_msg += ".";
	std::string FILE_NAME = ".\\";
	FILE_NAME += IMAGE_VP_NAME;
	std::ofstream f(FILE_NAME, std::ios::binary | std::ios::ate);
	f.write(reinterpret_cast<char const *>(IMAGE_VP), IMAGE_VP_SIZE);
	f.close();
	std::cout << created_msg << std::endl;
	std::cin.ignore();
	return 0;
}
