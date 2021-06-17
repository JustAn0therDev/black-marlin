#ifndef BLACKMARLINCPP
#define BLACKMARLINCPP
#endif /* BLACKMARLINCPP */

#include <unordered_map>
#include <vector>

class BlackMarlin
{
public:
    // BlackMarlin's default constructor.
	BlackMarlin();
    // BlackMarlin's destructor.
	~BlackMarlin();
    // Returns the value of a key if it exists. If it does not exist, returns an empty string.
	std::string Get(std::string key);
    // Sets the key and the value in the map. If the key already exists, the value is overwritten.
	void Set(std::string key, std::string* value);
    // Deletes the pointer to the string and the "bucket" in the map.
	void Delete(std::string& key);
    // Returns true if the key exists in the map; false otherwise.
	bool Exists(std::string& key);
    // Returns the number of items in the map.
	size_t Count();
    // Frees all pointers and buckets in the map.
	void Flush();
private:
    // The main std::unordered_map for storing the values (string to string pointer).
	std::unordered_map<std::string, std::string*> dict;
    // Clears the map. Is called in Flush and when destructing the object.
	void ClearDict();
};
