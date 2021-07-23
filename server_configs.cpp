#include "server_configs.hpp"
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <minwindef.h>
#include <utility>

ServerConfigs::ServerConfigs()
{
	this->m_configs = std::unordered_map<std::string, std::string>();
	this->m_filename = "bm_response_headers.txt";
}

void ServerConfigs::LoadHeadersFromConfigFile()
{
	std::string file_content, line_content;

	// TODO: Read Unix-based file paths. Currently this type of configuration is Windows-only.
	// A preprocessor should be here to check the current running OS.

	// the .txt name for configuring MUST BE "bm_response_headers.txt" and that the file
	// must be in the same directory as the running black_marlin binary.)
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

	std::cout << "Debugging below!!!" << "\n";
	auto& it = this->m_configs.begin();

	for (it; it != this->m_configs.end(); ++it)
	{
		std::cout << it->first << " = " << it->second << "\n";
	}
}

const std::unordered_map<std::string, std::string>& ServerConfigs::GetConfigs() const
{
	return this->m_configs;
}

const std::string ServerConfigs::GetThisExecutingBinaryFullPath() {
	bool found_binary = false;
	std::string full_path, path_part;

	char path_buffer[MAX_PATH];

	GetModuleFileName(NULL, path_buffer, MAX_PATH);

	while (!found_binary)
	{
		std::istringstream iss(path_buffer);

		while (std::getline(iss, path_part, PATH_DELIMETER))
		{
			if (path_part.find(".exe") != std::string::npos)
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
