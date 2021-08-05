#ifndef ARGPARSERCPP
#define ARGPARSERCPP

#include <string>

struct ArgParser
{
	// Tries to get the port value from an argument. If the input is invalid, a log is issued and the program terminates.
	static short GetPortFromArg(const char* arg_value) noexcept;
};

#endif /* ARGPARSERCPP */
