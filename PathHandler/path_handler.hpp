#include <string>

struct PathHandler
{
	// Gets the full path of the running binary.
	static const std::string GetThisExecutingBinaryFullPath() throw(...);
};
