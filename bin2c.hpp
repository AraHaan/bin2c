/*
	bin2c.hpp
*/

#ifndef HAVE_BIN2C_HPP
	#define HAVE_BIN2C_HPP
	#ifdef _WIN32
		#include <Windows.h>
	#elif __linux__
		//#include <unistd.h>
	#elif _MAC
		//Add missing includes here.
	#endif
	#include <string>
	#include <sstream>
	#include <iomanip>
	#include <filesystem>
	#include <fstream>
	#include <iostream>

	/*
		This method (CompileTimeHack()) is for processing the
		compile __TIME__ variable to strip extra spaces.
	*/
	std::string CompileTimeHack(std::string timevar);
	void WindowTitle();
	int FileExists(std::string &filename);
	void toolhead();
	void UsageList();
	void File_Processing(std::string &file1, std::string &file2, std::string &CustomVariable,
			std::string &_consolefilevar, std::string &_consolefilevar2, bool TargetCS);
	void ArgIterator(int argc, char** argv);
	int main(int argc, char** argv);
	std::string toHex(unsigned char const i);
	std::string ERROR_TAG_CONST = "ERROR: ";
	std::string BIN2C_VERSION = "0.14.0";
	std::string beta_label = "[BETA]";
	std::string alpha_label = "[ALPHA]";
	std::string final_label = "[FINAL]";
	std::string COMPILE_TIME = __TIME__;
	std::string COMPILE_DATE = __DATE__;
	#ifdef _WIN32
		std::string OS_NAME = "Windows";
		std::string ASSEMBLY_EXTENSION = ".exe";
		std::string REALEASE_LEVEL = final_label;
	#elif __linux__
		std::string OS_NAME = "Linux";
		std::string ASSEMBLY_EXTENSION = "";
		std::string REALEASE_LEVEL = final_label;
		std::string WINDOW_TITLE_FORMAT_CONST_START = "\033]2;";
		std::string WINDOW_TITLE_FORMAT_CONST_END = "\007\n\033[1A";
	#elif _MAC
		std::string OS_NAME = "MAC";
		std::string ASSEMBLY_EXTENSION = ".app";
		std::string REALEASE_LEVEL final_label;
		std::string WINDOW_TITLE_FORMAT_CONST_START = "\033]0;";
		std::string WINDOW_TITLE_FORMAT_CONST_END = "\007";
	#endif

	std::string WindowTitleName = "bin2c Conversion Tool v" + BIN2C_VERSION + " - " + OS_NAME + " - " + REALEASE_LEVEL;
	std::string FILE_HEAD = "/*\n\tFile Generated with bin2c Conversion Tool v" + BIN2C_VERSION + " - " + OS_NAME + " - " + REALEASE_LEVEL + ".\n\tFree for any use.\n\tCompiled on " + CompileTimeHack(COMPILE_DATE) + " at " + COMPILE_TIME + ".\n\tDO NOT MODIFY THIS FILE!!!\n*/\n/*\n\t";
	std::string USAGE_INFO = "Usage:\n\tbin2c" + ASSEMBLY_EXTENSION + " /custvar \"<variable here>\" /nohead\n\t\t/infile \"<file name here>.<ext>\"\n\t\t/outfile \"<file name here>.<c/h/cs>\"\n\t\t/basefolder \"<base folder the file is in>\" /target <c/cs>\n\n\t/custvar is for setting a custom variable name for the generated file\n\t\tarray.\n\t/nohead is for removing the tool's header printing stuff.\n\t/infile is for the base file to open to process to a Source or Header\n\t\tfile.\n\t/outfile is the name of the Source or Header file to write the\n\t\tgenerated contents to.\n\t/? or /help is for showing this Usage List.\n\t/basefolder is required to have file content Generation to be correct\n\t\ton the file name comment.\n\t/target is needed to generate C# arrays. Use '/target cs' for C#\n\t\tarrays. Defaults to c.";
	std::string TOOL_HEAD = "bin2c Conversion Tool v" + BIN2C_VERSION + ".\nFree for any use.";
	std::string IN_FILE_NOT_SPECIFIED_ERROR = ERROR_TAG_CONST + "\"/infile\" was not specified for a input file to process to a Source or header file.";
	std::string OUT_FILE_NOT_SPECIFIED_ERROR = ERROR_TAG_CONST + "\"/outfile\" was not specified for the processed file data.";
	std::string BASE_FOLDER_NOT_SPECIFIED_ERROR = ERROR_TAG_CONST + "\"/basefolder\" was not specified to help with correct code generation.";
	std::string PROCESSING_MSG_CONST_START = "Processing ";
	std::string PROCESSING_MSG_CONST_END = "...\n";
	std::string OUT_FILE_C_ARRAY_HEAD_CONST_START = "\n*/\n\nconst unsigned char ";
	std::string OUT_FILE_C_ARRAY_HEAD_CONST_MIDDLE = "[";
	std::string OUT_FILE_C_ARRAY_HEAD_CONST_END = "] = {\n";
	std::string OUT_FILE_CS_ARRAY_HEAD_CONST_START = "\n*/\n\nbyte[] ";
	std::string OUT_FILE_CS_ARRAY_HEAD_CONST_END = " = {\n";
	std::string OUT_FILE_ARRAY_START_TAB_CONST = "\t";
	std::string OUT_FILE_ARRAY_NEW_LINE_CONST = "\n\t";
	std::string OUT_FILE_ARRAY_END_NEW_LINE_CONST = "\n";
	std::string OUT_FILE_C_ARRAY_END_CONST_START = "};\n\nsize_t ";
	std::string OUT_FILE_C_ARRAY_END_CONST_MIDDLE1 = "_SIZE = ";
	std::string OUT_FILE_C_ARRAY_END_CONST_MIDDLE2 = ";\nconst char * ";
	std::string OUT_FILE_C_ARRAY_END_CONST_MIDDLE3 = "_NAME = \"";
	std::string OUT_FILE_C_ARRAY_END_CONST_END = "\";\n";
	std::string OUT_FILE_CS_ARRAY_END_CONST_START = "};\n\nint ";
	std::string OUT_FILE_CS_ARRAY_END_CONST_MIDDLE1 = "_SIZE = ";
	std::string OUT_FILE_CS_ARRAY_END_CONST_MIDDLE2 = ";\nchar[] ";
	std::string OUT_FILE_CS_ARRAY_END_CONST_MIDDLE3 = "_NAME = \"";
	std::string OUT_FILE_CS_ARRAY_END_CONST_END = "\";\n";
	std::string IN_FILE_DOES_NOT_EXIST_ERROR_CONST_START = ERROR_TAG_CONST + "The Input File '";
	std::string IN_FILE_DOES_NOT_EXIST_ERROR_CONST_END = "' does not exist.\n";
	std::string OUT_FILE_C_SUCCESS_CONST = " was successfully generated.\nBe sure to add it to your C/C++ Project file.\n";
	std::string OUT_FILE_CS_SUCCESS_CONST = " was successfully generated.\nBe sure to add it to your C# Project file.\n";
	std::string CUSTOM_VARIABLE_CONST = "a";
	std::string HELP_SWITCH_CONST = "/help";
	std::string QUESTION_MARK_SWITCH_CONST = "/?";
	std::string CUSTOM_VARIABLE_SWITCH_CONST = "/custvar";
	std::string NO_HEAD_SWITCH_CONST = "/nohead";
	std::string IN_FILE_SWITCH_CONST = "/infile";
	std::string OUT_FILE_SWITCH_CONST = "/outfile";
	std::string BASE_FOLDER_SWITCH_CONST = "/basefolder";
	std::string TARGET_TYPE_SWITCH_CONST = "/target";
	std::string EMPTY_STRING_CONST = "";

#endif /* bin2c.hpp */
