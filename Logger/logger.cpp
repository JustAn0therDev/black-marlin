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

void Logger::Log(const char* p_message) noexcept
{
    time_t now = time(0);

    const auto& current_local_time = localtime(&now);

    char* time_string_buffer = static_cast<char *>(malloc(sizeof(char) * TIME_STRING_SIZE));

    strftime(time_string_buffer, TIME_STRING_SIZE, "%Y-%m-%d %X", current_local_time);

    time_string_buffer = strcat(time_string_buffer, LOG_MESSAGE_DELIMETER);

    time_string_buffer = strcat(time_string_buffer, p_message);

    time_string_buffer = strcat(time_string_buffer, "\n");

    fputs(time_string_buffer, this->m_file);

    fflush(this->m_file);

    free(time_string_buffer);
}
