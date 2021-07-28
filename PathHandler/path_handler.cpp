#include <string>
#include "path_handler.hpp"
#include <sstream>
#include <cassert>

#if _WIN32 || _WIN64

#include <Windows.h>
#define PATH_DELIMETER '\\'

#else

#include <unistd.h>
#include <linux/limits.h>
#define PATH_DELIMETER '/'

#endif

const std::string PathHandler::GetThisExecutingBinaryFullPath() throw(...)
{
	constexpr unsigned long long SAFE_MAX_PATH = 4096;
	bool found_binary = false;

    std::string full_path = "", path_part, filename_part_to_look_for;

#if _WIN32 || _WIN64
	char path_buffer[MAX_PATH] = { '\0' };
    filename_part_to_look_for = "black_marlin.exe";
	GetModuleFileName(NULL, path_buffer, MAX_PATH);
#else
	char path_buffer[PATH_MAX] = { '\0' };
    filename_part_to_look_for = "black_marlin.file";
	readlink("/proc/self/exe", path_buffer, PATH_MAX);
#endif

	assert(("This binary's path should have been copied to the buffer.", strlen(path_buffer) > 0));

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
