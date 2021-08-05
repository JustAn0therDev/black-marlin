#include <string>
#include "path_handler.hpp"
#include <sstream>
#include <cstring>

#if _WIN32 || _WIN64

#include <Windows.h>
#define PATH_DELIMETER '\\'

#else

#include <unistd.h>
#include <climits>
#define PATH_DELIMETER '/'

#endif

const std::string PathHandler::GetThisExecutingBinaryFullPath()
{

	bool found_binary = false;

    std::string full_path = "", path_part, filename_part_to_look_for;

#if _WIN32 || _WIN64

	char path_buffer[MAX_PATH] = { '\0' };
    filename_part_to_look_for = "black-marlin.exe";
	GetModuleFileName(NULL, path_buffer, MAX_PATH);

#else

	char path_buffer[PATH_MAX] = { '\0' };
    filename_part_to_look_for = "black-marlin";
	readlink("/proc/self/exe", path_buffer, PATH_MAX);

#endif

	while (!found_binary)
	{
		std::string buf = std::string(path_buffer);

		std::istringstream iss(buf);

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

	return full_path;
}
