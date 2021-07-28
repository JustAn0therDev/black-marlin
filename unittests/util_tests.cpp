#include "catch2.hpp"
#include "../Util/util.hpp"
#include <iostream>

TEST_CASE("TryConvertStringToInt should return different from zero", "[TryConvertStringToInt]")
{
	std::string test = "234";
	REQUIRE(Util::TryCastStringToInt(test) == 234);
}

TEST_CASE("TryConvertStringToUnsignedShortInt should return different from zero", "[TryConvertStringToUnsignedShortInt]")
{
	std::string test = "234";
	REQUIRE(Util::TryCastStringToUnsignedShortInt(test) == 234);
}

TEST_CASE("TryConvertStringToInt test should throw exception", "[TryConvertStringToInt]")
{
    try
    {
        std::string test = "ASDF";
        Util::TryCastStringToInt(test);
        REQUIRE(false);
    }
    catch (...)
    {
        REQUIRE(true);
    }
}

TEST_CASE("TryConvertStringToUnsignedShortInt test should throw exception", "[TryConvertStringToUnsignedShortInt]")
{
    try
    {
        std::string test = "ASDFDFSFS";
        Util::TryCastStringToUnsignedShortInt(test);
        REQUIRE(false);
    }
    catch (...)
    {
        REQUIRE(true);
    }
}
