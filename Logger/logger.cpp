#include <string>
#include <ostream>
#include <fstream>
#include <cassert>
#include <time.h>
#include "../PathHandler/path_handler.hpp"
#include "logger.hpp"

void Logger::Log(std::string p_message) noexcept
{
	std::string full_path = Logger::GetLogFileFullPath();

	std::ofstream log_file_writer(full_path, std::ios::app);

	assert(("Log file should be good to read.", log_file_writer.good()));

	time_t now = time(0);

	tm* current_local_time = localtime(&now);

	char time_string_buffer[240];

	strftime(time_string_buffer, sizeof(time_string_buffer), "%Y-%m-%d %X", current_local_time);

	log_file_writer << time_string_buffer << " - " << p_message << "\n";

	free(current_local_time);
}

const std::string Logger::GetLogFileFullPath() noexcept
{
	return PathHandler::GetThisExecutingBinaryFullPath() + LOG_FILENAME;
}
