cmake_minimum_required (VERSION 3.8)

project ("black_marlin")

add_executable (black_marlin "main.cpp" "BlackMarlin/black_marlin.cpp" "BlackMarlin/black_marlin.hpp" "HTTP/httplib.h" "HTTP/status_code.hpp" "HTTP/http_request_handler.cpp" "HTTP/http_request_handler.hpp" "Util/util.cpp" "Util/util.hpp" "ServerConfigs/server_configs.cpp" "ServerConfigs/server_configs.hpp" "PathHandler/path_handler.cpp" "PathHandler/path_handler.hpp" "HTTP/server_connection_info.hpp" "Logger/logger.hpp" "Logger/logger.cpp")

enable_testing()
