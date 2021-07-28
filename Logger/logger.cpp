#include <string>
#include <ostream>
#include <fstream>
#include <cassert>
#include "../PathHandler/path_handler.hpp"
#include "logger.hpp"

void Logger::Log(std::string p_message) noexcept
{
    std::string full_path = Logger::GetLogFileFullPath();

    std::ofstream log_file_writer(full_path, std::ios::app);
    
    assert(("Log file should be good to read.", log_file_writer.good()));

    log_file_writer << "ERROR: " << p_message + "\n";
}

const std::string Logger::GetLogFileFullPath() noexcept
{
    return PathHandler::GetThisExecutingBinaryFullPath() + LOG_FILENAME;
}
