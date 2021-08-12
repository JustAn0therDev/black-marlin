#include "../Util/util.hpp"
#include "arg_parser.hpp"
#include <iostream>
#include <climits>
#include <regex>

long ArgParser::GetPortFromArg(const char* arg_value) noexcept
{
    char* buf;
	long port = std::strtol(arg_value, &buf, 10);

	return port;
}
