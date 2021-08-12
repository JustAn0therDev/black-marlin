#include <iostream>
#include "../vendor/catch2.hpp"
#include "../ArgParser/arg_parser.hpp"

TEST_CASE("Should parse port argument correctly.", "[GetPortFromArg]") 
{
    std::cout << "Running GetPortFromArg - Should parse port argument correctly.\n";
    REQUIRE(ArgParser::GetPortFromArg("1243") == 1243);
}

TEST_CASE("Should try to parse an invalid port argument and maybe return 0", "[GetPortFromArg]") 
{
    std::cout << "Running GetPortFromArg - Should try to parse an invalid port argument and return 0.\n";
    REQUIRE(ArgParser::GetPortFromArg("-2") == 0);
}

TEST_CASE("Should try to parse an invalid port argument and return 0", "[GetPortFromArg]") 
{
    std::cout << "Running GetPortFromArg - Should try to parse an invalid port argument and return 0.\n";
    REQUIRE(ArgParser::GetPortFromArg("utheasuaoeh") == 0);
}
