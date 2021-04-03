/*
	libargparse.hpp
*/
/*
	This library parses command line args.
*/

#ifndef LIBARGPARSE_DEFINED
#define LIBARGPARSE_DEFINED
#include "lib2hex.hpp"
#include <filesystem>
#include <iostream>
#ifdef _WIN32
	#include <Windows.h>
#endif

namespace fs = std::filesystem;


class libargparse {
public:
	template<typename T>
	void inline argreader(int argc, char* argv[], T &array1, T &array2) {
		if (argc > 2) {
			bool custvar_specified, nohead_specified, infile_specified, outfile_specified = false;
			for (int i = 1; i < argc; ++i) {
				tempstr = argv[i];
				if (tempstr == array1[33]) {
					custvar_value = argv[++i];
					custvar_specified = true;
				}
				if (tempstr == array1[34]) {
					nohead_specified = true;
				}
				if (tempstr == array1[35]) {
					fn = argv[++i];
					infile_specified = true;
				}
				if (tempstr == array1[36]) {
					fn2 = argv[++i];
					outfile_specified = true;
				}
				if (tempstr == array1[37]) {
					Target_Type = argv[++i];
					if (Target_Type == "cs") {
						use_cs_parse = true;
					}
				}
			}
			if (!nohead_specified) {
				std::cout << array1[2];
			}
			if (!infile_specified) {
				std::cout << array1[4];
			}
			if (!outfile_specified) {
				std::cout << array1[5];
			}
			if (!custvar_specified) {
				custvar_value = array1[8];
			}
			if (infile_specified && outfile_specified) {
				consolefilevar = fs::path(fn2).filename().string();
				consolefilevar2 = fs::path(fn).filename().string();
				lib2hex hexlib;
				hexlib.HexArraytofile(fn, fn2, custvar_value, consolefilevar,
					consolefilevar2, array1, use_cs_parse);
			}
		} else if (argc <= 2) {
			if (argc == 1) {
	#ifdef _WIN32
				SetConsoleTitleA(array1[0].c_str());
	#else
				std::cout << array2[3] << array1[0] << array2[4];
	#endif
				std::cout << array1[1] << std::endl;
				std::cin.get();
	#if !_WIN32
				std::cout << array2[3] << "" << array2[4];
	#endif
			} else {
				arg = argv[1];
				if (arg == array1[32]) {
					std::cout << array1[1] << std::endl;
					std::cin.get();
				} else if (arg == array1[31]) {
					std::cout << array1[1] << std::endl;
					std::cin.get();
				}
			}
		}
	}
	libargparse(void) {
		use_cs_parse = false;
	}
	~libargparse(void) {}
private:
	std::string fn, fn2, consolefilevar, consolefilevar2, custvar_value, Target_Type, tempstr, arg;
	bool use_cs_parse;
};

#endif
