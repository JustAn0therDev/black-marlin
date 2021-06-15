#include "black_marlin.hpp"

BlackMarlin::BlackMarlin()
{
	this->dict = std::unordered_map<std::string, std::string*>();
}

BlackMarlin::~BlackMarlin()
{
	this->Flush();
}

std::string BlackMarlin::Get(std::string& key)
{
    // I understand WHY it works, but not sure why the other one didn't with try-catching.
    auto it = this->dict.find(key);

    if (it != this->dict.end())
    {
      return *this->dict[key];
    }

    return "";
}

void BlackMarlin::Set(std::string key, std::string* value)
{
	this->dict[key] = value; // If the key exists, it is overwritten; otherwise creates a new one.
}

void BlackMarlin::Delete(std::string& key)
{
	auto it = this->dict.find(key);

	if (it != this->dict.end())
	{
		delete this->dict[key];
	}

	this->dict.erase(it);
}

bool BlackMarlin::Exists(std::string& key)
{
	auto it = this->dict.find(key);

	if (it != this->dict.end())
	{
		return true;
	}

	return false;
}

size_t BlackMarlin::Count()
{
	return this->dict.size();
}

void BlackMarlin::Flush()
{
	this->ClearDict();
}

size_t BlackMarlin::Strlen(std::string& key)
{
	return this->dict[key]->size();
}

void BlackMarlin::ClearDict()
{
	/* 
	* If just a reference is intended, the unary operator "&" should be used next to it and there is no need for dereferencing.
	*/
	for (auto& keyValuePair : this->dict)
	{
		delete keyValuePair.second;
	}

	this->dict.erase(this->dict.begin(), this->dict.end());
}
