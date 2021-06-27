#include "black_marlin.hpp"
#include <vector>
#include <iostream>
#include <thread>

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

void BlackMarlin::Set(std::string p_key, std::string* p_value) {
	auto it = this->m_dict.find(p_key);

	if (it == this->m_dict.end()) {
		this->m_dict[p_key] = p_value;
	}
}

void BlackMarlin::SetToDeleteLater(std::string p_key, std::string* p_value, const uint16_t& p_seconds) {
	auto& p_dict = this->m_dict;

	auto it = this->m_dict.find(p_key);

	if (it == this->m_dict.end()) {
		this->m_dict[p_key] = p_value;

		std::thread timer_daemon(&BlackMarlin::DeleteIn, this, p_key, p_seconds);
		timer_daemon.detach();
	}
}

void BlackMarlin::DeleteIn(const std::string& p_key, const uint16_t& p_seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(p_seconds));
	this->Delete(p_key);
}

void BlackMarlin::Overwrite(std::string p_key, std::string* p_value) {
	auto it = this->m_dict.find(p_key);

	if (it != this->m_dict.end()) {
		auto& current = m_dict[p_key];

		delete current;

		current = p_value;
	}
}

void BlackMarlin::Delete(const std::string& p_key) {
	auto it = this->m_dict.find(p_key);

	if (it == this->m_dict.end()) return;

	auto& current = this->m_dict[p_key];

	delete current;

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
	for (auto it = this->m_dict.begin(); it != this->m_dict.end(); ++it) {
		auto& current = this->m_dict[it->first];
		delete current;
		current = nullptr;
	}

	this->m_dict.clear();
}
