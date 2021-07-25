#!/bin/bash
g++ -pthread -std=c++11 ../black_marlin.hpp ../black_marlin.cpp ../util.hpp ../util.cpp catch2.hpp black_marlin_tests.cpp ../server_configs.hpp ../server_configs.cpp ../posix_pathfinder.hpp ../posix_pathfinder.cpp util_tests.cpp ../server_connection_info.hpp -o unittests
valgrind ./unittests
