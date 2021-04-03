/*
	libbin2cconstants.hpp
*/
#ifndef LIBBIN2CCONSTANTS_DEFINED
#define LIBBIN2CCONSTANTS_DEFINED
#ifdef _WIN32
#define _HAS_EXCEPTIONS 0
#endif
#include <string>
#include <vector>
#include "libargparse.hpp"

std::vector<std::string> base_array{"ERROR: ", "0.15.0", "[BETA]", "[ALPHA]", "[FINAL]", __TIME__, __DATE__};
#if defined(_WIN32) || defined(__CYGWIN__)
	std::vector<std::string> os_array{"Windows", ".exe", base_array[4]};
#elif __linux__
	std::vector<std::string> os_array{"Linux", "", base_array[4], "\033]2;", "\007\n\033[1A"};
#else
	std::vector<std::string> os_array{"MAC", "", base_array[4], "\033]0;", "\007"};
#endif

std::vector<std::string> bin2c_constants{
	"bin2c Conversion Tool v" + base_array[1] + " - " + os_array[0] + " - " + os_array[2],
	"Usage:\n\tbin2c" + os_array[1] + " /custvar \"<variable here>\" /nohead\n\t\t/infile \"<file name here>.<ext>\"\n\t\t/outfile \"<file name here>.<c/h/cs>\"\n\t\t/target <c/cs>\n\n\t/custvar is for setting a custom variable name for the generated file\n\t\tarray.\n\t/nohead is for removing the tool's header printing stuff.\n\t/infile is for the base file to open to process to a Source or Header\n\t\tfile.\n\t/outfile is the name of the Source or Header file to write the\n\t\tgenerated contents to.\n\t/? or /help is for showing this Usage List.\n\t/target is needed to generate C# arrays. Use '/target cs' for C#\n\t\tarrays. Defaults to c.",
	"bin2c Conversion Tool v" + base_array[1] + ".\nFree for any use.\n",
	"/*\n\tFile Generated with bin2c Conversion Tool v" + base_array[1] + " - " + os_array[0] + " - " + os_array[2] + ".\n\tFree for any use.\n\tCompiled on " + base_array[6] + " at " + base_array[5] + ".\n\tDO NOT MODIFY THIS FILE!!!\n*/\n/*\n\t",
	base_array[0] + "\"/infile\" was not specified for an input file to process to a Source or header file.\n",
	base_array[0] + "\"/outfile\" was not specified for the processed file data.\n",
	"Processing ", "...\n", "a", "\n*/\n\nconst unsigned char ", "[", "] = {\n",
	"\n*/\n\nbyte[] ", " = {\n", "\t", "\n\t", "\n", "};\n\nsize_t ", "_SIZE = ",
	";\nconst char * ", "_NAME = \"", "\";\n", "};\n\nint ", "_SIZE = ", ";\nchar[] ",
	"_NAME = \"", "\";\n", base_array[0] + "The Input File '", "' does not exist.\n",
	" was successfully generated.\n", " was successfully generated.\n",
	"/help", "/?", "/custvar", "/nohead", "/infile", "/outfile", "/target",
	"Be sure to add it to your C/C++ Project file.\n", "Be sure to add it to your C# Project file.\n"
};

void pass_constants(int argc, char* argv[]) {
	libargparse argparser;
	argparser.argreader(argc, argv, bin2c_constants, os_array);
}

#endif
