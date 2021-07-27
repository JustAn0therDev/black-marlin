#include <string>
#include "path_handler.hpp"
#include <sstream>

#if _WIN32 || _WIN64
#include <Windows.h>
#define PATH_DELIMETER '\\'
#else
#include <unistd.h>
#include <linux/limits.h>
#define PATH_DELIMETER '/'
#endif

const std::string PathHandler::GetThisExecutingBinaryFullPath()
{
	bool found_binary = false;
	char path_buffer[4096] = { '\0' };

    std::string full_path = "", path_part, filename_part_to_look_for;

#if _WIN32 || _WIN64
    filename_part_to_look_for = "black_marlin.exe";
	GetModuleFileName(NULL, path_buffer, (DWORD)240);
#else
    filename_part_to_look_for = "black_marlin.file";
	readlink("/proc/self/exe", path_buffer, (size_t)4096);
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
