#include <cstdint>
#include <string>
#include <vector>

#ifndef UTILCPP
#define UTILCPP
class Util {
public:
	// Tries casting a string to int. If not successful returns 0.
	static int TryCastStringToInt(const std::string& p_str);
	// Tries casting a string to an uint16_t. If not successful returns 0.
	static uint16_t TryCastStringToUnsignedShortInt(const std::string& p_str);
    // Writes a message to STDOUT, logs and ends the program's execution.
    static void Panic(const std::string& p_panic_message) noexcept;
};
#endif
