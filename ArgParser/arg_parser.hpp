#ifndef ARGPARSERCPP
#define ARGPARSERCPP

#include <string>

namespace ArgParser
{
    // Tries to get the port value from an argument. If the input is invalid, a log is issued and the program terminates.
    long GetPortFromArg(const char* arg_value) noexcept;
}

#endif /* ARGPARSERCPP */
