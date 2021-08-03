cmake_minimum_required (VERSION 3.8)

project ("black_marlin")

set(CMAKE_CXX_FLAGS "-std=c++11 -pthread -pedantic -Wall")

add_executable (black-marlin "main.cpp" "BlackMarlin/black_marlin.cpp" "BlackMarlin/black_marlin.hpp" "HTTP/httplib.h" "HTTP/status_code.hpp" "HTTP/http_request_handler.cpp" "HTTP/http_request_handler.hpp" "Util/util.cpp" "Util/util.hpp" "ServerConfigs/server_configs.cpp" "ServerConfigs/server_configs.hpp" "PathHandler/path_handler.cpp" "PathHandler/path_handler.hpp"  "Logger/logger.hpp" "Logger/logger.cpp" "ArgParser/arg_parser.cpp" "ArgParser/arg_parser.hpp"  )

enable_testing()
