#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "util.hpp"
#include "../Logger/logger.hpp"

int Util::TryCastStringToInt(const std::string& p_str)
{
	return std::stoi(p_str);
}

uint16_t Util::TryCastStringToUnsignedShortInt(const std::string& p_str)
{
	return static_cast<uint16_t>(std::stoi(p_str));
}

void Util::Panic(const std::string& p_panic_message) noexcept
{
	std::cout << p_panic_message;
	Logger::Log(p_panic_message);
	exit(1);
}
