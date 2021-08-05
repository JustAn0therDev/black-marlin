#!/bin/bash
g++ -pthread -std=c++17 ../BlackMarlin/black_marlin.hpp ../BlackMarlin/black_marlin.cpp ../Util/util.hpp ../Util/util.cpp catch2.hpp black_marlin_tests.cpp ../ServerConfigs/server_configs.hpp ../ServerConfigs/server_configs.cpp ../PathHandler/path_handler.cpp ../PathHandler/path_handler.hpp ../Logger/logger.hpp ../Logger/logger.cpp -o unittests
valgrind ./unittests
