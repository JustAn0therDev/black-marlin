#ifndef BLACKMARLINCPP
#define BLACKMARLINCPP
#endif /* BLACKMARLINCPP */

#include <unordered_map>

class BlackMarlin
{
private:
	std::unordered_map<std::string, std::string*> dict;
	void ClearDict();
public:
	BlackMarlin();
	~BlackMarlin();
	std::string Get(std::string& key);
	void Set(std::string key, std::string* value);
	void Delete(std::string& key);
	// a method Exists should be here so we can return a flag to the client informing if the value exists or not, instead of copying the whole thing back to it.
	bool Exists(std::string& key);
	size_t Count();
	void Flush();
	size_t Strlen(std::string& key);
};