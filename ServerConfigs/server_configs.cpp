#include "server_configs.hpp"
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <stdlib.h>

#if _WIN32 || _WIN64
#include "windows_pathfinder.hpp"
#else
#include "posix_pathfinder.hpp"
#endif

ServerConfigs::ServerConfigs()
{
	this->m_configs = std::unordered_map<std::string, std::string>();
	this->m_filename = "bm_response_headers.txt";
}

void ServerConfigs::LoadHeadersFromConfigFile()
{
	std::string file_content, line_content;

	char split_by = ' ';

	const std::string full_path = this->GetThisExecutingBinaryFullPath();

	std::ifstream response_headers_config_file(full_path, std::ios::in);

	if (response_headers_config_file.good())
	{
		while (std::getline(response_headers_config_file, file_content))
		{
			std::istringstream iss(file_content);

			auto& headers = this->GetHeaderPairFromConfigFile(iss, split_by);

			this->m_configs[headers.first] = headers.second;
		}
	}

	response_headers_config_file.close();
}

const std::unordered_map<std::string, std::string>& ServerConfigs::GetConfigs() const
{
	return this->m_configs;
}

const std::string ServerConfigs::GetThisExecutingBinaryFullPath() {
	bool found_binary = false;
	std::string full_path, path_part, path_buffer, filename_part_to_look_for;

#if _WIN32 || _WIN64
	path_buffer = GetCurrentlyExecutingBinaryPathWindows();
    filename_part_to_look_for = "black_marlin.exe";
#else
	path_buffer = GetCurrentlyExecutingBinaryPathPosix();
    filename_part_to_look_for = "black_marlin.file";
#endif

	while (!found_binary)
	{
		std::istringstream iss(path_buffer);

		while (std::getline(iss, path_part, PATH_DELIMETER))
		{
			if (path_part.find(filename_part_to_look_for) != std::string::npos)
			{
				found_binary = true;
				break;
			}

			full_path += path_part + PATH_DELIMETER;
		}
	}

	return full_path + this->m_filename;
}

const std::pair<std::string, std::string> ServerConfigs::GetHeaderPairFromConfigFile(std::istringstream& p_iss, char& p_split_by)
{
	std::string line_content, header_key, header_value = "";

	while (std::getline(p_iss, line_content, p_split_by))
	{
		if (header_key == "")
		{
			header_key = line_content;
		}
		else
		{
			header_value += line_content + ' ';
		}
	}

	return std::make_pair(header_key, header_value);
}
