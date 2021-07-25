#!/bin/bash
g++ -pthread -std=c++11 ../BlackMarlin/black_marlin.hpp ../BlackMarlin/black_marlin.cpp ../Util/util.hpp ../Util/util.cpp catch2.hpp black_marlin_tests.cpp ../ServerConfigs/server_configs.hpp ../ServerConfigs/server_configs.cpp ../ServerConfigs/posix_pathfinder.hpp ../ServerConfigs/posix_pathfinder.cpp util_tests.cpp ../HTTP/server_connection_info.hpp -o unittests
valgrind ./unittests
