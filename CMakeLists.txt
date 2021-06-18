# CMakeList.txt : CMake project for black_marlin, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("black_marlin")

# Add source to this project's executable.
add_executable (black_marlin "main.cpp" "black_marlin.cpp" "black_marlin.hpp" "httplib.h" "status_codes.hpp" "http_request_handler.cpp" "http_request_handler.hpp")

# TODO: Add tests and install targets if needed.
enable_testing()