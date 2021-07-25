#include <string>
#include <iostream>
#include "util.hpp"

int Util::TryCastStringToInt(const std::string& p_str)
{
	try {
		return std::stoi(p_str);
	}
	catch (...) {
		std::cout << "Tried convertion of invalid std::string to int. Tried converting the following data: " << p_str << "\n";
	}

	return 0;
}

uint16_t Util::TryCastStringToUnsignedShortInt(const std::string& p_str)
{
	try {
		return static_cast<uint16_t>(std::stoi(p_str));
	}
	catch (...) {
		std::cout << "Tried convertion of invalid std::string to uint16_t. Tried converting the following data: " << p_str << "\n";
	}

	return 0;
}

void Util::Panic(const std::string& p_panic_message)
{
    std::cout << p_panic_message;
    exit(1);
}
