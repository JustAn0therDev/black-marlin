#include <iostream>
#include <fstream>
#include "../vendor/catch2.hpp"
#include "../Logger/logger.hpp"
#include "../PathHandler/path_handler.hpp"

TEST_CASE("A log file should be created if it does not exist and the program should not crash while trying to log an error.", "[Log]") 
{
    std::cout << "Running Log - A log file should be created if it does not exist and the program should not crash while trying to log an error.\n";

    constexpr char LOG_FILENAME[] = "bm_logs.txt";
    remove(LOG_FILENAME);

    std::string full_filepath_with_filename = PathHandler::GetThisExecutingBinaryFullPath() + LOG_FILENAME;

    Logger logger;
    logger.Log("Testing log function.");

    REQUIRE(std::fstream(full_filepath_with_filename).good());
}
