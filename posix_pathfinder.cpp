#include <unistd.h>
#include <linux/limits.h>
#include "posix_pathfinder.hpp"

const std::string GetCurrentlyExecutingBinaryPathPosix()
{
	char path_buffer[PATH_MAX] = { '\0' };
	readlink("/proc/self/exe", path_buffer, PATH_MAX);

	return std::string(path_buffer);
}
