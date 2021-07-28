#include "server_configs.hpp"
#include "../PathHandler/path_handler.hpp"
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <stdlib.h>

static constexpr char BM_RESPONSE_HEADERS_FILENAME[24] = "bm_response_headers.txt";

ServerConfigs::ServerConfigs() noexcept
{
	this->m_configs = std::unordered_map<std::string, std::string>();
}

void ServerConfigs::LoadHeadersFromConfigFile()
{
	std::string file_content, line_content;

	const char split_by = ' ';

	const std::string full_path = PathHandler::GetThisExecutingBinaryFullPath() + BM_RESPONSE_HEADERS_FILENAME;

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

const std::unordered_map<std::string, std::string>& ServerConfigs::GetConfigs() const noexcept
{
	return this->m_configs;
}

const std::pair<std::string, std::string> ServerConfigs::GetHeaderPairFromConfigFile(std::istringstream& p_iss, const char& p_split_by)
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
			header_value += line_content + p_split_by;
		}
	}

	// Removing the trailing whitespace character.
	return std::make_pair(header_key, header_value.erase(header_value.size() - 1, 1));
}
