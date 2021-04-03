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
#if _WIN32
	std::string FILE_NAME = ".\\";
#else
	std::string FILE_NAME = "./";
#endif
	FILE_NAME += IMAGE_VP_NAME;
	std::ofstream f(FILE_NAME, std::ios::binary | std::ios::ate);
	f.write(reinterpret_cast<char const *>(IMAGE_VP), IMAGE_VP_SIZE);
	f.close();
	std::cout << created_msg << std::endl;
	return 0;
}
