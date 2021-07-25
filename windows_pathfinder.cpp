#include <Windows.h>
#include "windows_pathfinder.hpp"

const std::string GetCurrentlyExecutingBinaryPathWindows()
{
	char path_buffer[MAX_PATH] = { '\0' };
	GetModuleFileName(NULL, path_buffer, MAX_PATH);

	return std::string(path_buffer);
}
