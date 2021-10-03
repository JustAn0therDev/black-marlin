#include <string>
#include <iostream>
#include "util.hpp"

void Util::Panic(const char* p_panic_message) noexcept
{
    std::cout << p_panic_message;
    exit(1);
}
