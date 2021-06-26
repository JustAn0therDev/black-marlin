#include "black_marlin.hpp"
#include <vector>
#include <iostream>
#include <thread>

void BlackMarlin::DeleteIn(const std::string& p_key, const int& p_seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(p_seconds));
	this->Delete(p_key);
}

BlackMarlin::BlackMarlin() {
	this->m_dict = std::unordered_map<std::string, std::string*>();
}

BlackMarlin::~BlackMarlin() {
	this->Flush();
}

std::string* BlackMarlin::Get(const std::string& p_key) const {
	auto it = this->m_dict.find(p_key);

	if (it != this->m_dict.end()) {
		return it->second;
	}

	return nullptr;
}

void BlackMarlin::Set(std::string p_key, std::string*& p_value) {
	auto it = this->m_dict.find(p_key);

	if (it == this->m_dict.end()) {
		this->m_dict[p_key] = p_value;
	}
}

void BlackMarlin::SetWithTimer(std::string p_key, std::string*& p_value, const int& p_seconds) {
	auto& p_dict = this->m_dict;

	auto it = this->m_dict.find(p_key);

	if (it == this->m_dict.end()) {
		this->m_dict[p_key] = p_value;
		std::thread new_timer_thread(&BlackMarlin::DeleteIn, this, p_key, p_seconds);
		new_timer_thread.detach();
	}
}

void BlackMarlin::Overwrite(std::string p_key, std::string*& p_value) {
	auto it = this->m_dict.find(p_key);

	if (it != this->m_dict.end()) {
		delete m_dict[p_key];
		m_dict[p_key] = p_value;
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
		auto& current_key = this->m_dict[it->first];

		delete current_key;

		/*
		 * At this point, "this->m_dict[it->first]" has to point to nullptr so that it won't throw a heap corruption error.
		 * This happens because the iterator might call its value or check for a value in the key. This ends up as an invalid read.
		 * Since the read checks for nullptr first, the pointers must be set to nullptr before any further operation, indicating that a pointer is not pointing to a valid memory region anymore.
		 */
		current_key = nullptr;
	}

	this->m_dict.clear();
}
