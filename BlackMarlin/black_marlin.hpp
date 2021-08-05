#ifndef BLACKMARLINCPP
#define BLACKMARLINCPP

#include <unordered_map>
#include <vector>

class BlackMarlin {
public:
	BlackMarlin() noexcept;
	~BlackMarlin() noexcept;
	// Returns the value of a key if it exists. If it does not exist, returns a nullptr.
	const std::string& Get(const std::string& p_key) const;
	// Sets the key and the value in the map. If the key already exists and the intention was to overwrite the value, the method Overwrite should be used instead.
	void Set(std::string p_key, const std::string& p_value);
	// Sets the key and the value in the map to be deleted later in the specified amount of seconds.
	void SetToDeleteLater(std::string p_key, const std::string& p_value, const uint16_t& p_seconds);
	// Overwrites the value to the key. If the key does not exist, nothing happens.
	void Overwrite(std::string p_key, const std::string& p_value);
	// Deletes the pointer to the string and the "bucket" in the map.
	void Delete(const std::string& p_key);
	// Returns true if the key exists in the map; false otherwise.
	bool Exists(const std::string& p_key) const;
	// Returns the number of items in the map.
	size_t Count() const noexcept;
	// Frees all pointers and buckets in the map.
	void Flush();
private:
	// The main std::unordered_map for storing the values (string to string pointer).
	std::unordered_map<std::string, std::string> m_dict;
	// Deletes the pointer in the specified time in seconds.
	void DeleteIn(const std::string& p_key, const uint16_t& p_seconds);
    // A null value so that there is a default value as response when a key is not found.
    std::string m_null_string_value = "\0";
};

#endif /* BLACKMARLINCPP */
