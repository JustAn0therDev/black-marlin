#include <string>
#include <iostream>
#include "util.hpp"
#include "../Logger/logger.hpp"

void Util::Panic(const std::string& p_panic_message) noexcept
{
	std::cout << p_panic_message;
	Logger::Log(p_panic_message);
	exit(1);
}
