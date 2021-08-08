#include "black_marlin.hpp"
#include <iostream>
#include <thread>
#include <vector>

BlackMarlin::BlackMarlin() noexcept
{
	this->m_dict = std::unordered_map<std::string, std::string>();
}

BlackMarlin::~BlackMarlin() noexcept
{
	this->Flush();
}

const std::string& BlackMarlin::Get(const std::string& p_key) const
{
	const auto it = this->m_dict.find(p_key);

	if (it != this->m_dict.end())
	{
		return it->second;
	}

	return this->m_default_empty_value;
}

void BlackMarlin::Set(const std::string& p_key, const std::string& p_value)
{
    const auto it = this->m_dict.find(p_key);

	if (it == this->m_dict.end())
	{
		this->m_dict[p_key] = p_value;
	}
}

void BlackMarlin::SetToDeleteLater(const std::string& p_key, const std::string& p_value, const uint16_t& p_seconds)
{
	const auto it = this->m_dict.find(p_key);

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

void BlackMarlin::Overwrite(const std::string& p_key, const std::string& p_value)
{
    const auto it = this->m_dict.find(p_key);

	if (it != this->m_dict.end())
	{
		this->m_dict[p_key] = p_value;
	}
}

void BlackMarlin::Delete(const std::string& p_key)
{
    const auto it = this->m_dict.find(p_key);

	if (it == this->m_dict.end()) return;

	this->m_dict.erase(it);
}

bool BlackMarlin::Exists(const std::string& p_key) const
{
	const auto it = this->m_dict.find(p_key);

	if (it != this->m_dict.end())
	{
		return true;
	}

	return false;
}

size_t BlackMarlin::Count() const noexcept
{
	return this->m_dict.size();
}

void BlackMarlin::Flush()
{
    this->m_dict.clear();
}
