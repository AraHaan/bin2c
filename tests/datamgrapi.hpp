/*
	datamgrapi.hpp
*/

#ifdef __CPLUSPLUS
extern "C" {
#endif

#pragma once
#ifdef DATAMGRAPI_EXPORTS
	#include "hidenfuncs.hpp"
	#define DATAMGRAPI_EXTERN extern "C" __declspec(dllexport)
	DATAMGRAPI_EXTERN int volatile __cdecl data_mgr(std::string method, const char * filename, size_t size_of_data, const char * mode, const void *ptr, const char * msg, bool keep_alive);
#else
	#define DATAMGRAPI_EXTERN extern "C" __declspec(dllimport)
	DATAMGRAPI_EXTERN int volatile data_mgr(std::string method, const char * filename, size_t size_of_data, const char * mode, const void *ptr, const char * msg, bool keep_alive);
#endif

#ifdef __CPLUSPLUS
}
#endif
