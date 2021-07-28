#include "arg_parser.hpp"
#include <regex>
#include "../Util/util.hpp"

short ArgParser::GetPortFromArg(const char* arg_value) noexcept
{
	short port = 0;
	std::regex only_numbers_pattern("[0-9]+");

	if (regex_match(arg_value, only_numbers_pattern))
	{
		port = std::atoi(arg_value);
	}
	else
		Util::Panic("Expected only numbers for port argument. Got: " + std::string(arg_value) + "\n");

	if (port > USHRT_MAX)
		Util::Panic("The port argument exceeds the range of valid ports.");

	return port;
}
