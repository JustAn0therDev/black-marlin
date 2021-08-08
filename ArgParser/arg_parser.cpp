#include "../Util/util.hpp"
#include "arg_parser.hpp"
#include <climits>
#include <regex>

long ArgParser::GetPortFromArg(const char* arg_value) noexcept
{
	long port = 0;
	std::regex only_numbers_pattern("[0-9]+");
	Util util;
	char* buf;

	// TODO: does this track negative integers conversion?
	port = std::strtol(arg_value, &buf, 10);

	if (port == 0)
		util.Panic("Conversion of port number did not succeed. Got the following value as argument: "
		+ std::string(arg_value) + "\n");

	if (port > USHRT_MAX || port < 0)
	    util.Panic("The port argument value exceeds the range of valid ports.");

	return port;
}
