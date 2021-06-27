#include <cstdint>
#include <string>

#ifndef UTILCPP
#define UTILCPP
class Util {
public:
	// Tries casting a string to int. If not successful, returns 0.
	static int TryCastStringToInt(std::string& p_str);
	// Tries casting a string to an uint16_t. If not successful, returns 0.
	static uint16_t TryCastStringToUnsignedShortInt(std::string& p_str);
};
#endif