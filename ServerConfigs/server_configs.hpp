#ifndef SERVERCONFIGSCPP
#define SERVERCONFIGSCPP

#include <unordered_map>
#include <string>
#include <sstream>
#include <utility>

class ServerConfigs
{
public:
	// Loads the internal hashtable with the configs file's content.
	void LoadHeadersFromConfigFile();
	// Returns a const reference to the hashtable.
	const std::unordered_map<std::string, std::string>& GetConfigs() const noexcept;
private:
	// This object's internal hashtable.
	std::unordered_map<std::string, std::string> m_configs;
	// Returns the header information (being it key and value) from the config file's current line.
	static std::pair<std::string, std::string> GetHeaderPairFromConfigFile(std::istringstream& p_iss, const char& p_split_by);
};

#endif /* SERVERCONFIGSCPP */
