#include "black_marlin.hpp"
#include <vector>

BlackMarlin::BlackMarlin() {
	this->dict = std::unordered_map<std::string, std::string*>();
}

BlackMarlin::~BlackMarlin() {
	this->Flush();
}

std::string BlackMarlin::Get(std::string& key) {
    // I understand WHY it works, but not sure why the other one didn't work (using a try catch).
    auto it = this->dict.find(key);

    if (it != this->dict.end()) {
        return *this->dict[key];
    }

    return "";
}

void BlackMarlin::Set(std::string key, std::string* value) {
	this->dict[key] = value; // If the key exists, it is overwritten; otherwise creates a new one.
}

void BlackMarlin::Delete(std::string& key) {
    auto it = this->dict.find(key);

    if (it != this->dict.end()) {
        delete this->dict[key];
    }
    
	this->dict.erase(key); // this should work. It doesn't work when not using raw pointers.
}

bool BlackMarlin::Exists(std::string& key) {
	auto it = this->dict.find(key);

	if (it != this->dict.end()) {
		return true;
	}

	return false;
}

size_t BlackMarlin::Count() {
	return this->dict.size();
}

void BlackMarlin::Flush() {
	this->ClearDict();
}

void BlackMarlin::ClearDict() {
    // cleaning up pointers in buckets.
    for (auto it = this->dict.begin(); it != this->dict.end(); ++it) {
        delete it->second;
    }

    // cleaning up buckets themselves.
    this->dict.erase(this->dict.begin(), this->dict.end());
    
    // The problem here is that I delete the value and read it again,
    // when iterating. This is wrong, the deletion should not occur like this, rather
    // clean the std::string pointers first and then erasing the buckets.    
}

std::vector<std::string> BlackMarlin::GetAll() {
    std::vector<std::string> vectToReturn = std::vector<std::string>();

    for (auto& pair : this->dict)
    {
        vectToReturn.push_back(pair.first + " " + *pair.second);
    }

    return vectToReturn;
}
