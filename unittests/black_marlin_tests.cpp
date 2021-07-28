#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "../BlackMarlin/black_marlin.hpp"
#include <thread>

auto black_marlin = BlackMarlin();

TEST_CASE("Black Marlin Get and Set Tests", "[Get and Set]")
{
	std::cout << "Running Get and Set - Set should create a key-value pair in the map and get should return the value associated to the key.\n";

	std::string* deletable_val = new std::string("get and set test");
	std::string sample_key = "get and set test";
	black_marlin.Set(sample_key, deletable_val);

	const std::string* value = black_marlin.Get(sample_key);

	REQUIRE(*value != "");
	REQUIRE(*value == "get and set test");
}

TEST_CASE("Set with timer tests", "[Set with timer]")
{
	const uint16_t seconds = 5;
	std::cout << "Running Set with Timer - Should set a key to expire in five seconds, and the 'get' command after it should return nullptr.\n";

	std::string key = "get and set with timer test";
	std::string* value = new std::string("get and set with timer test");

	black_marlin.SetToDeleteLater(key, value, seconds);

	std::this_thread::sleep_for(std::chrono::seconds(6));

	REQUIRE(!black_marlin.Exists(key));
	REQUIRE(black_marlin.Get(key) == nullptr);
}

TEST_CASE("Overwrite tests", "[Overwrite]")
{
	std::cout << "Running Overwrite - Should overwrite the value associated to the key.\n";
	
	std::string sample_key = "get and set test";
	std::string* val = new std::string("get and set test two");
	black_marlin.Overwrite(sample_key, val);

	const std::string* value = black_marlin.Get(sample_key);

	REQUIRE(*value == "get and set test two");
}

TEST_CASE("Exists Tests", "[Exists]")
{
	std::cout << "Running Exists - Should return true.\n";

	std::string key = "get and set test";

	REQUIRE(black_marlin.Exists(key));
}

TEST_CASE("Delete Tests", "[Delete]")
{
	std::cout << "Running Delete - Delete should remove the key from the std::unordered_map and clear the std::string*.\n";

	std::string key = "get and set test";
	black_marlin.Delete(key);

	REQUIRE(black_marlin.Count() == 0);
}

TEST_CASE("Count Test", "[Count]")
{
	std::cout << "Running Count - Should return 1 after inserting a key.\n";

	std::string sample_key = "get and set test";
	std::string* value = new std::string("test value");
	black_marlin.Set(sample_key, value);

	REQUIRE(black_marlin.Count() == 1);
}

TEST_CASE("Flush Test", "[Flush]")
{
	std::cout << "Running Flush - Should run without heap corruption and Count should return 0.\n";

	black_marlin.Flush();

	REQUIRE(black_marlin.Count() == 0);
}
