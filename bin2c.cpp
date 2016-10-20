/*
	bin2c.cpp
*/
/*
	Changes in v0.14.0:

	1. Changed Header File to not have any defines except for the multi-platform
		include guard.
	2. Replaced strcmp() usage from the C Library. It is a bad habbit to use
		C stuff including C style casts in C++ anyway.
	3. removed string.h from bin2c.hpp because strcmp was not in <string>
		making me have to include that anyway. Now that strcmp is not used don't
		need that header anymore.
	4. Removed the last snprintf(). Now I don't need to make unneccessary buffers
		line a C programmer would. Why would people need buffers for C++ anyway?
		Buffers in C++ is bad because what if someone forgets to free or delete
		everything in it?
*/

#include "bin2c.hpp"

#ifdef _WIN32

void WindowTitle() {
	SetConsoleTitleA(WindowTitleName.c_str());
}

#else

void WindowTitle() {
	std::cout << WINDOW_TITLE_FORMAT_CONST_START << WindowTitleName << WINDOW_TITLE_FORMAT_CONST_END;
}

#endif

std::string toHex(unsigned char const i)
{
	std::stringstream stream;
	stream << "0x" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned short>(i);
	return stream.str();
}

int FileExists(std::string &filename) {
	return std::experimental::filesystem::exists(filename);
}

std::string CompileTimeHack(std::string timevar) {
	std::size_t found = timevar.find("  ");
	if (found != std::string::npos) {
		timevar.replace(found, 2, " ");
	}
	return timevar;
}

void toolhead() {
	std::cout << TOOL_HEAD << std::endl;
}

void UsageList() {
	std::cout << USAGE_INFO << std::endl;
	std::cin.get();
}

void File_Processing(std::string &file1, std::string &file2, std::string &CustomVariable,
		std::string &_consolefilevar, std::string &_consolefilevar2, bool TargetCS) {
	bool F_OPEN_ERROR = false;
	if (FileExists(file1)) {
		std::ifstream f(file1, std::ios::in | std::ios::binary | std::ios::ate);
		std::string data;
		unsigned long n = 0;
		data = FILE_HEAD;
		data += _consolefilevar;
		std::cout << PROCESSING_MSG_CONST_START << _consolefilevar2 << PROCESSING_MSG_CONST_END;
		unsigned long file_size = static_cast<unsigned long>(std::streamoff(f.tellg()));
		if (!TargetCS) {
			data += OUT_FILE_C_ARRAY_HEAD_CONST_START;
			data += CustomVariable;
			data += OUT_FILE_C_ARRAY_HEAD_CONST_MIDDLE;
			data += std::to_string(file_size);
			data += OUT_FILE_C_ARRAY_HEAD_CONST_END;
		}
		else {
			data += OUT_FILE_CS_ARRAY_HEAD_CONST_START;
			data += CustomVariable;
			data += OUT_FILE_CS_ARRAY_HEAD_CONST_END;
		}
		if (f.is_open()) {
			unsigned char* memblock = new unsigned char[file_size];
			f.seekg(0, std::ios::beg);
			f.read(reinterpret_cast<char *>(memblock), file_size);
			for (unsigned int l = 0; l < file_size; l++) {
				int ch;
				if (n == 0) {
					data += OUT_FILE_ARRAY_START_TAB_CONST;
				}
				ch = static_cast<int>(memblock[l]);
				data += toHex(ch) + ", ";
				++n;
				if (n % 16 == 0) {
					data = data.replace(data.length() - 1, 1, OUT_FILE_ARRAY_NEW_LINE_CONST);
				}
			}
			delete[] memblock;
			data = data.replace(data.length() - 2, 2, OUT_FILE_ARRAY_END_NEW_LINE_CONST);
			if (!TargetCS) {
				data += OUT_FILE_C_ARRAY_END_CONST_START;
				data += CustomVariable;
				data += OUT_FILE_C_ARRAY_END_CONST_MIDDLE1;
				data += std::to_string(file_size);
				data += OUT_FILE_C_ARRAY_END_CONST_MIDDLE2;
				data += CustomVariable;
				data += OUT_FILE_C_ARRAY_END_CONST_MIDDLE3;
				data += _consolefilevar2;
				data += OUT_FILE_C_ARRAY_END_CONST_END;
			}
			else {
				data += OUT_FILE_CS_ARRAY_END_CONST_START;
				data += CustomVariable;
				data += OUT_FILE_CS_ARRAY_END_CONST_MIDDLE1;
				data += std::to_string(file_size);
				data += OUT_FILE_CS_ARRAY_END_CONST_MIDDLE2;
				data += CustomVariable;
				data += OUT_FILE_CS_ARRAY_END_CONST_MIDDLE3;
				data += _consolefilevar2;
				data += OUT_FILE_CS_ARRAY_END_CONST_END;
			}
			std::ofstream f2(file2, std::ios::out | std::ios::binary | std::ios::ate);
			f2 << data;
			f2.close();
			f.close();
		}
	}
	else {
		F_OPEN_ERROR = true;
		std::cout << IN_FILE_DOES_NOT_EXIST_ERROR_CONST_START << file1 << IN_FILE_DOES_NOT_EXIST_ERROR_CONST_END;
	}
	if (!F_OPEN_ERROR) {
		if (!TargetCS) {
			std::cout << _consolefilevar << OUT_FILE_C_SUCCESS_CONST;
		}
		else {
			std::cout << _consolefilevar << OUT_FILE_CS_SUCCESS_CONST;
		}
	}
}

void ArgIterator(int argc, char** argv) {
	std::string fn;
	std::string fn2;
	std::string basefolder;
	std::string consolefilevar;
	std::string consolefilevar2;
	std::string custvar_value;
	std::string Target_Type;
	bool custvar_specified = false;
	bool nohead_specified = false;
	bool infile_specified = false;
	bool outfile_specified = false;
	bool basefolder_specified = false;
	bool Target_Type_specified = false;
	bool USE_CS_PARSE = false;
	for (int i = 1; i < argc; i++) {
		if (static_cast<std::string>(argv[i]) == CUSTOM_VARIABLE_SWITCH_CONST) {
			custvar_value = argv[i + 1];
			custvar_specified = true;
		}
		if (static_cast<std::string>(argv[i]) == NO_HEAD_SWITCH_CONST) {
			nohead_specified = true;
		}
		if (static_cast<std::string>(argv[i]) == IN_FILE_SWITCH_CONST) {
			fn = argv[i + 1];
			infile_specified = true;
		}
		if (static_cast<std::string>(argv[i]) == OUT_FILE_SWITCH_CONST) {
			fn2 = argv[i + 1];
			outfile_specified = true;
		}
		if (static_cast<std::string>(argv[i]) == BASE_FOLDER_SWITCH_CONST) {
			basefolder = argv[i + 1];
			basefolder_specified = true;
		}
		if (static_cast<std::string>(argv[i]) == TARGET_TYPE_SWITCH_CONST) {
			Target_Type = argv[i + 1];
			Target_Type_specified = true;
			if (Target_Type == "cs") {
				USE_CS_PARSE = true;
			}
		}
	}
	if (!nohead_specified) {
		toolhead();
	}
	if (!infile_specified) {
		std::cout << IN_FILE_NOT_SPECIFIED_ERROR << std::endl;
	}
	if (!outfile_specified) {
		std::cout << OUT_FILE_NOT_SPECIFIED_ERROR << std::endl;
	}
	if (!custvar_specified) {
		custvar_value = EMPTY_STRING_CONST;
	}
	if (!Target_Type_specified) {
		Target_Type = "c";
	}
	if (!basefolder_specified) {
		std::cout << BASE_FOLDER_NOT_SPECIFIED_ERROR << std::endl;
	}
	else {
		if (infile_specified == true && outfile_specified == true) {
			std::string original_fn2 = fn2;
			std::string original_fn = fn;
			consolefilevar = fn2.replace(0, basefolder.length(), EMPTY_STRING_CONST);
			consolefilevar2 = fn.replace(0, basefolder.length(), EMPTY_STRING_CONST);
			fn2 = original_fn2;
			fn = original_fn;
			if (custvar_value == EMPTY_STRING_CONST) {
				custvar_value = CUSTOM_VARIABLE_CONST;
			}
			File_Processing(fn, fn2, custvar_value, consolefilevar, consolefilevar2, USE_CS_PARSE);
		}
	}
}

int main(int argc, char** argv) {
	if (argc > 2) {
		ArgIterator(argc, argv);
	}
	else if (argc <= 2) {
		if (argc == 1) {
			WindowTitle();
			UsageList();
		}
		else if (static_cast<std::string>(argv[1]) == QUESTION_MARK_SWITCH_CONST) {
			UsageList();
		}
		else if (static_cast<std::string>(argv[1]) == HELP_SWITCH_CONST) {
			UsageList();
		}
	}
	return 0;
}
