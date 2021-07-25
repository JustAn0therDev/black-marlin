#include <Windows.h>
#include "windows_pathfinder.hpp"

const std::string GetCurrentlyExecutingBinaryPathWindows()
{
	char path_buffer[MAX_PATH];
	GetModuleFileName(NULL, path_buffer, MAX_PATH);

	return std::string(path_buffer);
}
