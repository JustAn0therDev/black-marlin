#include <string>
#include "path_handler.hpp"
#include <sstream>
#include <iostream>

#if _WIN32 || _WIN64

#include <Windows.h>
#define PATH_DELIMETER '\\'

#else

#include <unistd.h>
#include <climits>
#define PATH_DELIMETER '/'

#endif

std::string PathHandler::GetThisExecutingBinaryFullPath()
{
	bool found_binary = false;
    std::string full_path, path_part, filename_part_to_look_for;

#if _WIN32 || _WIN64

	char path_buffer[MAX_PATH] = { '\0' };
    filename_part_to_look_for = "black-marlin.exe";
	GetModuleFileName(NULL, path_buffer, MAX_PATH);

#else

	char path_buffer[PATH_MAX] = { '\0' };
    filename_part_to_look_for = "black-marlin";
	auto bytes_read = readlink("/proc/self/exe", path_buffer, PATH_MAX);

	if (bytes_read == -1) {
	    std::cout << "Could not read the binary's path in the system.\n";
        exit(1);
	}

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
