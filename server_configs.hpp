#include <unordered_map>
#include <string>
#include <sstream>
#include <utility>

#if _WIN32
#define PATH_DELIMETER '\\'
#else 
#define PATH_DELIMETER '\'
#endif

#ifndef SERVERCONFIGSCPP
#define SERVERCONFIGSCPP
class ServerConfigs 
{
public:
	ServerConfigs();
	// Loads the internal hashtable with the configs file's content.
	void LoadHeadersFromConfigFile();
	// Returns a const reference to the hashtable
	const std::unordered_map<std::string, std::string>& GetConfigs() const;
private:
	// This object's internal hashtable.
	std::unordered_map<std::string, std::string> m_configs;
	// The current operating system's path delimeter.
	// The header configs file name.
	std::string m_filename;
	// Gets the correct path for the config file.
	const std::string GetThisExecutingBinaryFullPath();
	// Returns the object's internal hashtable for reading only.
	const std::unordered_map<std::string, std::string> GetConfigsFromFile() const;
	// Returns the header information (being it key and value) from the config file's current line.
	const std::pair<std::string, std::string> GetHeaderPairFromConfigFile(std::istringstream& p_iss, char& p_split_by);
};
#endif /* SERVERCONFIGSCPP */
