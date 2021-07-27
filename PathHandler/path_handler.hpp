#include <string>

struct PathHandler
{
public:
	// Gets the full path of the running binary.
	static const std::string GetThisExecutingBinaryFullPath();
};
