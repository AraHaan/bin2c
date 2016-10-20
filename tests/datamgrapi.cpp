/*
	datamgrapi.cpp
*/

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <string>
#include <iostream>
#include "datamgrapi.hpp"

/*
	Original Implementation of a API for writing files and compressing/decompressing them without needing zlib in your own project.
	Maybe someday we can also add in Crypto++ support for those who like / use that thing in a much hopefully easier way.
	Also I would like for this to also support to somehow have a function that can modify the actual files through zlib with
	compression / decompression as well as one that would be pointer based data compression / decompression if possible.
	As Well as some sort of simplified way of getting CRC's using zlib's built in CRC checker. (For file formats that requires a well formed CRC32)

	Added in Test 10: 
	+ mode arg for the filesave function.
	+ method arg for the data_mgr function.
	+ keep_alive arg for the data_mgr function.
	+ mode arg for the data_mgr function.

	Goal:
		A simplified use of opening files to save data and to Allow easy use of Compression and Decompressions using zlib and for easy getting of File CRC32's
		Less than 10 Exports.
*/

HINSTANCE DATAMGRAPI;

int volatile filesave(const char * filename, size_t size_of_data, const char * mode, const void *ptr)
{
	if (!strcmp(mode, "wb") && !strcmp(mode, "w") && !strcmp(mode, "w+") && !strcmp(mode, "wb+") && !strcmp(mode, "a") && !strcmp(mode, "a+") && !strcmp(mode, "ab") && !strcmp(mode, "ab+"))
	//if (!strcmp(mode, "wb+w+ab+a+")) I do not think this line is the same as the one right above.
	{
		return 0;
	}
	//TODO: Check if file exists and if so alert the user and return.
	FILE* f = fopen(filename, mode);
	fwrite(ptr, 1, size_of_data, f);
	fclose(f);
	return 0;
}

int volatile keep_alive_until_enter_key_is_pressed()
{
	std::cin.ignore().get();
	return 0;
}

DATAMGRAPI_EXTERN int volatile __cdecl data_mgr(std::string method, const char * filename, size_t size_of_data, const char * mode, const void *ptr, const char * msg, bool keep_alive)
{
	if (method == "save")
	{
		filesave(filename, size_of_data, mode, ptr);
		std::cout << msg << std::endl;
		if (keep_alive)
		{
			keep_alive_until_enter_key_is_pressed();
		}
	}
	else if (method == "compress")
	{
		//TODO: Add a zlib Compression method.
		std::cout << "Sorry, zlib Compression is not implemented yet.\nHowever it is planned for this function to also allow setting the compression level." << std::endl;
		if (keep_alive)
		{
			keep_alive_until_enter_key_is_pressed();
		}
	}
	else if (method == "decompress")
	{
		//TODO: Add a zlib Decompression method.
		std::cout << "Sorry, zlib Decompression is not implemented yet." << std::endl;
		if (keep_alive)
		{
			keep_alive_until_enter_key_is_pressed();
		}
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hDLL, DWORD reason, LPVOID reserved)
{
	switch (reason) {
		case DLL_PROCESS_ATTACH:
			DATAMGRAPI=hDLL;
			DisableThreadLibraryCalls(hDLL);
			break;
	}
	return TRUE;
}
