#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "../black_marlin.hpp"

BlackMarlin black_marlin = BlackMarlin();

TEST_CASE("Black Marlin Get and Set Tests", "[Get and Set]")
{
	std::cout << "Running Get and Set - Set should create a key-value pair in the map and get should return the value associated to the key." << std::endl;

	std::string sample_key = "get and set test";

	black_marlin.Set(sample_key, &sample_key);

	std::string value = black_marlin.Get(sample_key);
	REQUIRE(value != "");
	REQUIRE(value == "get and set test");
}

TEST_CASE("Overwrite tests", "[Overwrite]")
{
	std::cout << "Running Overwrite - Should overwrite the value associated to the key." << std::endl;

	std::string sample_key = "get and set test";
	std::string val = "get and set test two";

	black_marlin.Overwrite(sample_key, &val);

	std::string value = black_marlin.Get(sample_key);
	REQUIRE(value == "get and set test two");
}

TEST_CASE("Exists Tests", "[Exists]")
{
	std::cout << "Running Exists - Should return true." << std::endl;

    std::string key = "get and set test";
	REQUIRE(black_marlin.Exists(key));
}

TEST_CASE("Delete Tests", "[Delete]")
{
	std::cout << "Running Delete - Delete should remove the key from the std::unordered_map and clear the std::string*." << std::endl;

    std::string key = "get and set test";
    black_marlin.Delete(key);

    REQUIRE(black_marlin.Count() == 0);
}

TEST_CASE("Count Test", "[Count]")
{
	std::cout << "Running Count - Should return 1 after inserting a key." << std::endl;

    std::string sample_key = "get and set test";

	black_marlin.Set(sample_key, &sample_key);

	REQUIRE(black_marlin.Count() == 1);
}

TEST_CASE("Flush Test", "[Flush]")
{
	std::cout << "Running Flush - Should run without heap corruption and Count should return 0." << std::endl;

    black_marlin.Flush();
    REQUIRE(black_marlin.Count() == 0);
}
