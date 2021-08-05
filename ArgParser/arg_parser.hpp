#ifndef ARGPARSERCPP
#define ARGPARSERCPP

#include <string>

struct ArgParser
{
	// Tries to get the port value from an argument. If the input is invalid, the program terminates (since this function is called by the entrypoint).
	static short GetPortFromArg(const char* arg_value) noexcept;
};

#endif /* ARGPARSERCPP */
