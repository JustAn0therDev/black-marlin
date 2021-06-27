#!/bin/bash

g++ -pthread -std=c++17 black_marlin.cpp black_marlin.hpp httplib.h main.cpp http_request_handler.cpp http_request_handler.hpp util.hpp util.cpp -o black_marlin
valgrind --leak-check=full ./black_marlin
