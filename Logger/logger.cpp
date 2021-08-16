#include "../PathHandler/path_handler.hpp"
#include "logger.hpp"
#include <ctime>
#include <ostream>
#include <string>
#include <iostream>

Logger::Logger()
{
    this->m_full_filepath = PathHandler::GetThisExecutingBinaryFullPath() + LOG_FILENAME;
}

void Logger::Log(const std::string& p_message) noexcept
{
    // This "fstream" CANNOT be out of scope because of RAII (even when using pointers).
    auto fstream = std::ofstream(this->m_full_filepath, std::ios::app);

    time_t now = time(0);

    tm* current_local_time = localtime(&now);

    char time_string_buffer[21];

    strftime(time_string_buffer, sizeof(time_string_buffer), "%Y-%m-%d %X", current_local_time);

    fstream << time_string_buffer << " - " << p_message << "\n";
}
