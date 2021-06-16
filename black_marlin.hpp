#ifndef BLACKMARLINCPP
#define BLACKMARLINCPP
#endif /* BLACKMARLINCPP */

#include <unordered_map>
#include <vector>

class BlackMarlin
{
public:
	BlackMarlin();
	~BlackMarlin();
	std::string Get(std::string& key);
	void Set(std::string key, std::string* value);
	void Delete(std::string& key);
	bool Exists(std::string& key);
	size_t Count();
	void Flush();
    std::vector<std::string> GetAll();
private:
	std::unordered_map<std::string, std::string*> dict;
	void ClearDict();
};
