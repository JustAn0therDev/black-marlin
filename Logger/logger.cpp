#include "../PathHandler/path_handler.hpp"
#include "logger.hpp"
#include <ctime>
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

Logger::Logger()
{
    this->m_full_filepath = PathHandler::GetThisExecutingBinaryFullPath() + LOG_FILENAME;
    this->m_file = fopen(this->m_full_filepath.c_str(), "a");
}

Logger::~Logger()
{
    fclose(this->m_file);
}

void Logger::Log(const std::string& p_message) noexcept
{
    time_t now = time(0);

    tm* current_local_time = localtime(&now);

    char time_string_buffer[30];

    strftime(time_string_buffer, sizeof(time_string_buffer), "%Y-%m-%d %X", current_local_time);

    const auto& message = strcat(time_string_buffer, LOG_MESSAGE_DELIMETER) + p_message + "\n";

    fputs(message.c_str(), this->m_file);
}
