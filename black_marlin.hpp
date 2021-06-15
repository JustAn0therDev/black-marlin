#include <unordered_map>

// TODO: The value must be a pointer, but the returned value in the Get method has to be a copy so it can be written by the server in the response.
class BlackMarlin
{
private:
	std::unordered_map<std::string, std::string*> dict; // should this be a pointer? So a flush could just "erase" it and build another one "from scratch"?
public:
	BlackMarlin();
	~BlackMarlin();
	std::string Get(std::string& key);
	void Set(std::string key, std::string* value);
	void Overwrite(std::string key, std::string* newValue);
	void Delete(std::string& key);
	bool Exists(std::string& key); // a method Exists should be here so we can return a flag to the client informing if the value exists or not, instead of copying the whole thing back to it.
	unsigned int Count();
	void Flush();
	std::string Strlen(std::string& key);
};