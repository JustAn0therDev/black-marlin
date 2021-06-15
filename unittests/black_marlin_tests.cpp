#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "../black_marlin.hpp"

auto blackMarlin = BlackMarlin();

TEST_CASE("Black Marlin Get and Set Tests", "[Get and Set]")
{
	std::cout << "Running Get and Set" << std::endl;

	std::string sampleKey = "get and set test";
  std::string anotherSampleKey = "get and set test two";

	std::string& sampleReference = sampleKey;

	blackMarlin.Set(sampleKey, new std::string(sampleKey));
	REQUIRE(blackMarlin.Count() == 1);

  blackMarlin.Set(anotherSampleKey, new std::string(anotherSampleKey));

	std::string value = blackMarlin.Get(sampleKey);
	REQUIRE(value != "");
	REQUIRE(value == "get and set test");
}

TEST_CASE("Exists Tests", "[Exists]")
{
	std::cout << "Running Exists" << std::endl;

  std::string key = "get and set test";
	std::string& ref = key;
	REQUIRE(blackMarlin.Exists(key));
}

TEST_CASE("Delete Tests", "[Delete]")
{
	std::cout << "Running Delete" << std::endl;

  std::string key = "get and set test";
	std::string& ref = key;
  blackMarlin.Delete(ref);

  REQUIRE(blackMarlin.Count() == 1);
}

TEST_CASE("Count Test", "[Count]")
{
	std::cout << "Running Count" << std::endl;

	REQUIRE(blackMarlin.Count() == 1);
}

TEST_CASE("Strlen Test", "[Strlen]")
{
	std::cout << "Running Strlen" << std::endl;

  std::string key = "get and set test two";
	std::string& keyRef = key;
  REQUIRE(blackMarlin.Strlen(keyRef) == 20);
}

TEST_CASE("Flush Test", "[Flush]")
{
	std::cout << "Running Flush" << std::endl;

  blackMarlin.Flush();
  REQUIRE(blackMarlin.Count() == 0);
}
