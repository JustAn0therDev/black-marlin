#include <string>
#include <iostream>
#include "util.hpp"

int Util::TryCastStringToInt(std::string& p_str) {
	try {
		return std::stoi(p_str);
	}
	catch (std::exception ex) {
		std::cout << "Tried convertion of invalid std::string to int. Exception message: " << ex.what() << "\n";
	}
	catch (...) {
		std::cout << "Tried convertion of invalid std::string to int. No std::exception thrown. " << "\n";
	}

	return 0;
}

uint16_t Util::TryCastStringToUnsignedShortInt(std::string& p_str) {
	try {
		return std::stoi(p_str);
	}
	catch (std::exception ex) {
		std::cout << "Tried convertion of invalid std::string to uint16_t. Exception message: " << ex.what() << "\n";
	}
	catch (...) {
		std::cout << "Tried convertion of invalid std::string to uint16_t. No std::exception thrown. " << "\n";
	}

	return 0;
}
