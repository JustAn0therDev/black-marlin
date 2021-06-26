#include <string>
#include "util.hpp"
#include <iostream>

int Util::TryConvertStringToInt(std::string& p_str) {
	try {
		return std::stoi(p_str);
	}
	catch (std::exception& ex) {
		std::cout << "Tried convertion of invalid string to int. Exception message: " << ex.what() << "\n";
	}

	return 0;
}
