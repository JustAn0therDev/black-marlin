#include "black_marlin.hpp"
#include <vector>
#include <iostream>

BlackMarlin::BlackMarlin() {
	this->m_dict = std::unordered_map<std::string, std::string*>();
}

BlackMarlin::~BlackMarlin() {
	this->Flush();
}

std::string BlackMarlin::Get(std::string p_key) {
    auto it = this->m_dict.find(p_key);

    if (it != this->m_dict.end()) {
        return *this->m_dict[p_key];
    }

    return "";
}

void BlackMarlin::Set(std::string p_key, std::string* p_value) {
    auto it = this->m_dict.find(p_key);

    if (it == this->m_dict.end()) {
        this->m_dict[p_key] = p_value;
    }
}

void BlackMarlin::Overwrite(std::string p_key, std::string* p_value) {
    auto it = this->m_dict.find(p_key);

    if (it != this->m_dict.end()) {
        delete this->m_dict[p_key];
        this->m_dict[p_key] = p_value;
    }
}

void BlackMarlin::Delete(std::string& p_key) {
    auto it = this->m_dict.find(p_key);

    if (it != this->m_dict.end()) {
        delete this->m_dict[p_key];
    }
    
	this->m_dict.erase(p_key);
}

bool BlackMarlin::Exists(std::string& p_key) {
	auto it = this->m_dict.find(p_key);

	if (it != this->m_dict.end()) {
		return true;
	}

	return false;
}

size_t BlackMarlin::Count() {
	return this->m_dict.size();
}

void BlackMarlin::Flush() {
	this->ClearDict();
}

void BlackMarlin::ClearDict() {
    // cleaning up pointers in buckets.
    for (auto it = this->m_dict.begin(); it != this->m_dict.end(); ++it) {
        delete it->second;
    }

    // cleaning up the buckets if there are any.
    this->m_dict.erase(this->m_dict.begin(), this->m_dict.end());
}
