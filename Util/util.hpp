#ifndef UTILCPP
#define UTILCPP

#include <cstdint>
#include <string>
#include "../Logger/logger.hpp"

class Util
{
public:
    // Writes a message to STDOUT, logs and ends the program's execution.
    void Panic(const std::string& p_panic_message) noexcept;
private:
    Logger m_logger;
};

#endif /* UTILCPP */
