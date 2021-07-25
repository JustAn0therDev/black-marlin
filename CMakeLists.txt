cmake_minimum_required (VERSION 3.8)

project ("black_marlin")

add_executable (black_marlin "main.cpp" "black_marlin.cpp" "black_marlin.hpp" "httplib.h" "status_code.hpp" "http_request_handler.cpp" "http_request_handler.hpp" "util.cpp" "util.hpp" "server_configs.cpp" "server_configs.hpp" "windows_pathfinder.cpp" "server_connection_info.hpp")

enable_testing()