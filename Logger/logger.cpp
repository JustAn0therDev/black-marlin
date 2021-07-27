#include <string>
#include <ostream>
#include <fstream>
#include <cassert>
#include "../PathHandler/path_handler.hpp"
#include "logger.hpp"

void Logger::LogInfo(std::string p_message)
{
    std::string full_path = Logger::GetLogFileFullPath();

    std::ofstream log_file_writer(full_path);

    assert(("The file must be good to read even if didn't exist before.", log_file_writer.good()));

    log_file_writer << "INFO: " << p_message << "\n";
    log_file_writer.close();
}

void Logger::LogWarning(std::string p_message)
{
    std::string full_path = Logger::GetLogFileFullPath();
    
    std::ofstream log_file_writer(full_path);

    assert(("The file must be good to read even if didn't exist before.", log_file_writer.good()));

    log_file_writer << "WARNING: " << p_message << "\n";
    log_file_writer.close();
}

void Logger::LogError(std::string p_message)
{
    std::string full_path = Logger::GetLogFileFullPath();

    std::ofstream log_file_writer(full_path);

    assert(("The file must be good to read even if didn't exist before.", log_file_writer.good()));

    log_file_writer << "ERROR: " << p_message << "\n";
    log_file_writer.close();
}

const std::string Logger::GetLogFileFullPath()
{
    return PathHandler::GetThisExecutingBinaryFullPath() + LOG_FILENAME;
}
