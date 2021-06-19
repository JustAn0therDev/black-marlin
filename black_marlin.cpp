#include "black_marlin.hpp"
#include <vector>
#include <iostream>

BlackMarlin::BlackMarlin() {
	this->m_dict = std::unordered_map<std::string, std::string*>();
}

BlackMarlin::~BlackMarlin() {
	this->Flush();
}

std::string BlackMarlin::Get(const std::string& p_key) const {
    auto it = this->m_dict.find(p_key);

    if (it != this->m_dict.end()) {
        return *it->second;
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

void BlackMarlin::Delete(const std::string& p_key) {
    auto it = this->m_dict.find(p_key);

    if (it == this->m_dict.end()) return;

    delete this->m_dict[p_key];
    
	this->m_dict.erase(p_key);
}

bool BlackMarlin::Exists(const std::string& p_key) const {
	auto it = this->m_dict.find(p_key);

	if (it != this->m_dict.end()) {
		return true;
	}

	return false;
}

size_t BlackMarlin::Count() const {
	return this->m_dict.size();
}

void BlackMarlin::Flush() {
	this->ClearDict();
}

void BlackMarlin::ClearDict() {
    for (auto it = this->m_dict.begin(); it != this->m_dict.end(); ++it) {
        delete this->m_dict[it->first];
        /*
         * At this point, "this->m_dict[it->first]" has to point to NULL so that it won't throw a heap corruption error. 
         * This happens because the iterator might call its value or check for a value in the key. This ends up as an invalid read.
         * Since the read checks for NULL first, the pointers must be set to NULL before any further operation, indicating that a pointer is not pointing to a valid memory region anymore.
        */
        this->m_dict[it->first] = NULL;
    }

    this->m_dict.clear();
}
