/*
	VP.cpp
*/

#include <string>
#include <iostream>
#ifdef __linux__
	#include <string.h>

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

	int volatile data_mgr(std::string method, const char * filename, size_t size_of_data, const char * mode, const void *ptr, const char * msg, bool keep_alive)
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

#elif _WIN32
#include "datamgrapi.hpp"
#endif
#include "VP.hpp"

std::string NAME_FILTER = ".\\";

int main()
{
	std::string created_msg = "Created ";
	created_msg += IMAGE_VP_NAME;
	created_msg += ".";
	std::string FILE_NAME = NAME_FILTER + IMAGE_VP_NAME;
	data_mgr("save", FILE_NAME.c_str(), IMAGE_VP_SIZE, "wb", IMAGE_VP, created_msg.c_str(), true);
	return 0;
}
