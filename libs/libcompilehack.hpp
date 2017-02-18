/*
	libcompilehack.hpp
*/

#ifndef LIBCOMPILEHACK_DEFINED
#define LIBCOMPILEHACK_DEFINED
namespace libcompilehack {
	std::string inline CompileDateHack(std::string &timevar) {
		std::size_t found = timevar.find("  ");
		if (found != std::string::npos) {
			timevar.replace(found, 2, " ");
		}
		return timevar;
	}
}

#endif
