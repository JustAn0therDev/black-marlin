#include <string>
#include "path_handler.hpp"
#include <sstream>
#include <iostream>

#include <unistd.h>
#include <climits>
#define PATH_DELIMETER '/'

std::string PathHandler::GetThisExecutingBinaryFullPath()
{
    bool found_binary = false;
    std::string full_path, path_part, filename_part_to_look_for;

#if defined(linux) || defined(__linux) || defined(__linux__)

    char path_buffer[PATH_MAX] = { '\0' };
    filename_part_to_look_for = "blackmarlin";
    auto bytes_read = readlink("/proc/self/exe", path_buffer, PATH_MAX);

    if (bytes_read == -1) 
    {
        std::cout << "Could not read the path to get to this binary. Please check the permissions for the user logged in.\n";
        exit(1);
    }

#else
#error PLATFORM NOT SUPPORTED
    exit(1);
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
