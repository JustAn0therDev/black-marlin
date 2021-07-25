#include "catch2.hpp"
#include "../ServerConfigs/server_configs.hpp"
#include <iostream>

ServerConfigs server_configs;

TEST_CASE("Load configs from file should read the demo file and the configs should have only one pair in the hashtable.", "[TryConvertStringToInt]")
{
	server_configs.LoadHeadersFromConfigFile();
	const auto& configs = server_configs.GetConfigs();
	REQUIRE(configs.size() == 1);
}