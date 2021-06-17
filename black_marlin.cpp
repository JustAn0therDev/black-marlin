#include "black_marlin.hpp"
#include <vector>
#include <iostream>

BlackMarlin::BlackMarlin() {
	this->dict = std::unordered_map<std::string, std::string*>();
}

BlackMarlin::~BlackMarlin() {
	this->Flush();
}

std::string BlackMarlin::Get(std::string key) {
    auto it = this->dict.find(key);

    if (it != this->dict.end()) {
        return *this->dict[key];
    }

    return "";
}

void BlackMarlin::Set(std::string key, std::string* value) {
	this->dict[key] = value;
}

void BlackMarlin::Delete(std::string& key) {
    auto it = this->dict.find(key);

    if (it != this->dict.end()) {
        delete this->dict[key];
    }
    
	this->dict.erase(key);
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

    // cleaning up the buckets.
    this->dict.erase(this->dict.begin(), this->dict.end());
}
