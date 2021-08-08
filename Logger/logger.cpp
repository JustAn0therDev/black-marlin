#include "../PathHandler/path_handler.hpp"
#include "logger.hpp"
#include <ctime>
#include <ostream>
#include <string>

Logger::Logger()
{
   std::string full_path = Logger::GetLogFileFullPath();
   this->m_log_file_writer = std::ofstream(Logger::GetLogFileFullPath(), std::ios::app);
}

void Logger::Log(const std::string& p_message) noexcept
{
	time_t now = time(0);

	tm* current_local_time = localtime(&now);

	char time_string_buffer[21];

	strftime(time_string_buffer, sizeof(time_string_buffer), "%Y-%m-%d %X", current_local_time);

	this->m_log_file_writer << time_string_buffer << " - " << p_message << "\n";
}

std::string Logger::GetLogFileFullPath() noexcept
{
	return PathHandler::GetThisExecutingBinaryFullPath() + LOG_FILENAME;
}
