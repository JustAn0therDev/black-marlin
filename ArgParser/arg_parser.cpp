#include "../Util/util.hpp"
#include "arg_parser.hpp"
#include <iostream>
#include <climits>
#include <regex>

long ArgParser::GetPortFromArg(const char* arg_value) noexcept
{
    const std::regex only_numbers("^[0-9]+$");

    if (!std::regex_match(arg_value, only_numbers)) {
        // Will not parse the chars with strtol if it contains anything that is not a number.
        return 0;
    }

    char* buf;
	long port = std::strtol(arg_value, &buf, 10);

	return port;
}
