/*
	lib2hex.hpp
*/
/*
	This library converts data to hex.
*/
#ifndef LIB2HEX_DEFINED
#define LIB2HEX_DEFINED
#include <iostream>
#include <fstream>
#include "hexstream"

class lib2hex {
public:
	template<typename T>
	std::string inline fileToHexArray(std::string &file, std::string &CustomVariable,
			std::string &_consolefilevar, std::string &_consolefilevar2, T &array, bool TargetCS) {
		n = 0;
		std::fstream f(file, std::ios::in | std::ios::binary | std::ios::ate);
		if (f.good()) {
			data = array[3];
			data += _consolefilevar;
			std::cout << array[6] << _consolefilevar2 << array[7];
			file_size = static_cast<uint64_t>(std::streamoff(f.tellg()));
			if (!TargetCS) {
				data += array[9] + CustomVariable + array[10] +
					std::to_string(file_size) + array[11];
			} else {
				data += array[12] + CustomVariable + array[13];
			}
			if (f.is_open()) {
				memblock = new uint8_t[file_size];
				f.seekg(0, std::ios::beg);
				f.read(reinterpret_cast<char *>(memblock), file_size);
				AraHaan::hexstream stream(true, true, 16, file_size, false, memblock);
				stream << f;
				stream >> data;
				delete[] memblock;
				data = data.replace(data.length() - 2, 2, array[16]);
				if (!TargetCS) {
					data += array[17] + CustomVariable + array[18] +
						std::to_string(file_size) + array[19] + CustomVariable +
						array[20] + _consolefilevar2 + array[21];
				} else {
					data += array[22] + CustomVariable + array[23] +
						std::to_string(file_size) + array[24] + CustomVariable +
						array[25] + _consolefilevar2 + array[26];
				}
				f.close();
				return data;
			}
		} else {
			std::cout << array[27] << file << array[28];
		}
		return "";
	}
	template<typename T>
	void inline HexArraytofile(std::string &file1, std::string &file2, std::string &CustomVariable,
			std::string &_consolefilevar, std::string &_consolefilevar2, T &array, bool TargetCS) {
		filedata = fileToHexArray(file1, CustomVariable, _consolefilevar, _consolefilevar2,
			array, TargetCS);
		std::fstream f2(file2, std::ios::out | std::ios::binary | std::ios::app);
		f2 << filedata;
		f2.close();
		if (!TargetCS) {
			std::cout << _consolefilevar << array[29];
			#ifdef _WIN32
				std::cout << array[38];
			#endif
		} else {
			std::cout << _consolefilevar << array[30];
			#ifdef _WIN32
				std::cout << array[39];
			#endif
		}
	}
	lib2hex(void) {
		n = 0;
		file_size = 0;
	}
	~lib2hex(void) {}
private:
	uint64_t n;
	uint64_t file_size;
	std::string data;
	uint8_t* memblock;
	std::string filedata;
};

#endif
