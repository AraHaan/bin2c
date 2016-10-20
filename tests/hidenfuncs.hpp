/*
	hidenfuncs.hpp
*/

/*
	HIDDEN FUNCTIONS TO THIS API DLL THAT ONLY IT HAS.
*/

//THESE CANNOT BE USED OUTSIDE OF THIS DLL. THEY MUST NOT BE KNOWN EITHER.
int volatile keep_alive_until_enter_key_is_pressed();
int volatile filesave(std::string filename, size_t size_of_data, const char * mode, const void *ptr);
