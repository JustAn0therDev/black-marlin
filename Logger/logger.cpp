#include "../PathHandler/path_handler.hpp"
#include "logger.hpp"
#include <ctime>
#include <fstream>
#include <ostream>
#include <string>

void Logger::Log(std::string p_message) noexcept
{
	std::string full_path = Logger::GetLogFileFullPath();

	std::ofstream log_file_writer(full_path, std::ios::app);

	time_t now = time(0);

	tm* current_local_time = localtime(&now);

    // I don't want to make this buffer bigger. Although I got no idea how this would overflow, does not seem like a bad idea to have a bigger buffer.
    // But I don't see the need for it right now either. So its staying 21 bytes for now.
	char time_string_buffer[21];

	strftime(time_string_buffer, sizeof(time_string_buffer), "%Y-%m-%d %X", current_local_time);

	log_file_writer << time_string_buffer << " - " << p_message << "\n";
}

const std::string Logger::GetLogFileFullPath() noexcept
{
	return PathHandler::GetThisExecutingBinaryFullPath() + LOG_FILENAME;
}
