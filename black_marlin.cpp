#include "black_marlin.hpp"

BlackMarlin::BlackMarlin()
{
	this->dict = std::unordered_map<std::string, std::string*>();
}

BlackMarlin::~BlackMarlin()
{
	/* 
	 * If just a reference is intended, the unary operator "&" should be used next to it and no need for dereferencing as well. 
	 */
	for (auto& key : this->dict)
	{
		delete this->dict[key];
	}
}

std::string* BlackMarlin::Get(std::string& key)
{
	try
	{
		return this->dict[key];
	}
	catch (std::string& key)
	{
		// TODO: I got no idea what to do with this std::string& key.
		return nullptr;
	}
}

void BlackMarlin::Set(std::string key, std::string* value)
{
	this->dict[key] = value;
}

void BlackMarlin::Overwrite(std::string key, std::string* newValue)
{
	if (this->dict.find(key))
	{
		delete this->dict[key];
		this->dict[key] = newValue;
	}
}

void BlackMarlin::Delete(std::string& key)
{
	if (this->dict.find(key))
	{
		delete this->dict[key]; // TODO: should this make the std::unordered_map size smaller or just make the key have a nullptr value?
	}
}

bool BlackMarlin::Exists(std::string& key)
{
	return this->dict.find(key) ? true : false;
}

unsigned int BlackMarlin::Count()
{
	return this->dict.size();
}

void BlackMarlin::Flush()
{
	for (auto& key : this->dict)
	{
		this->dict.erase(key);
	}
}

std::string BlackMarlin::Strlen(std::string& key)
{
	return std::string();
}
