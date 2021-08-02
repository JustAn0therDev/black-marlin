#include "black_marlin.hpp"
#include <vector>
#include <iostream>
#include <thread>

BlackMarlin::BlackMarlin() noexcept
{
	this->m_dict = std::unordered_map<std::string, std::string*>();
}

BlackMarlin::~BlackMarlin() noexcept
{
	this->Flush();
}

const std::string* BlackMarlin::Get(const std::string& p_key) const
{
	const auto& it = this->m_dict.find(p_key);

	if (it != this->m_dict.end())
	{
		return it->second;
	}

	return nullptr;
}

void BlackMarlin::Set(std::string p_key, std::string* p_value)
{
    const auto& it = this->m_dict.find(p_key);

	if (it == this->m_dict.end())
	{
		this->m_dict[p_key] = p_value;
	}
}

void BlackMarlin::SetToDeleteLater(std::string p_key, std::string* p_value, const uint16_t& p_seconds)
{
	const auto& it = this->m_dict.find(p_key);

	if (it == this->m_dict.end())
	{
		this->m_dict[p_key] = p_value;

		std::thread timer_daemon(&BlackMarlin::DeleteIn, this, p_key, p_seconds);
		timer_daemon.detach();
	}
}

void BlackMarlin::DeleteIn(const std::string& p_key, const uint16_t& p_seconds)
{
	std::this_thread::sleep_for(std::chrono::seconds(p_seconds));
	this->Delete(p_key);
}

void BlackMarlin::Overwrite(std::string p_key, std::string* p_value)
{
    const auto& it = this->m_dict.find(p_key);

	if (it != this->m_dict.end())
	{
		delete this->m_dict[p_key];

		this->m_dict[p_key] = p_value;
	}
}

void BlackMarlin::Delete(const std::string& p_key)
{
    const auto& it = this->m_dict.find(p_key);

	if (it == this->m_dict.end()) return;

	delete this->m_dict[p_key];

	this->m_dict.erase(it);
}

const bool BlackMarlin::Exists(const std::string& p_key) const
{
	const auto& it = this->m_dict.find(p_key);

	if (it != this->m_dict.end())
	{
		return true;
	}

	return false;
}

const size_t BlackMarlin::Count() const noexcept
{
	return this->m_dict.size();
}

void BlackMarlin::Flush()
{
	for (auto& it = this->m_dict.begin(); it != this->m_dict.end(); ++it)
	{
		delete it->second;
		it->second = nullptr;
	}

    this->m_dict.clear();
}
