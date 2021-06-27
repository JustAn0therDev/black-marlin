#include "catch2.hpp"
#include "../util.hpp"
#include <iostream>

TEST_CASE("Util TryConvertStringToInt should return different from zero", "[TryConvertStringToInt]")
{
	std::string test = "234";
	REQUIRE(Util::TryCastStringToInt(test) == 234);
}

TEST_CASE("TryConvertStringToUnsignedShortInt should return different from zero", "[TryConvertStringToUnsignedShortInt]")
{
	std::string test = "234";
	REQUIRE(Util::TryCastStringToUnsignedShortInt(test) == 234);
}

TEST_CASE("Util TryConvertStringToInt test should return zero", "[TryConvertStringToInt]")
{
	std::string test = "ASDF";
	REQUIRE(Util::TryCastStringToInt(test) == 0);
}

TEST_CASE("Util TryConvertStringToUnsignedShortInt test should return zero", "[TryConvertStringToUnsignedShortInt]")
{
	std::string test = "ASDFDFSFS";
	REQUIRE(Util::TryCastStringToUnsignedShortInt(test) == 0);
}