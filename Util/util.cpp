#include <string>
#include <iostream>
#include "util.hpp"

void Util::Panic(const std::string& p_panic_message) noexcept
{
    std::cout << p_panic_message;
    this->m_logger.Log(p_panic_message);
    exit(1);
}
