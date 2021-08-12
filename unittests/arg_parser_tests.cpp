#include "../vendor/catch2.hpp"
#include "../ArgParser/arg_parser.hpp"

TEST_CASE("Should parse port argument correctly.", "[GetPortFromArg]") 
{
    REQUIRE(ArgParser::GetPortFromArg("1243") == 1243);
}