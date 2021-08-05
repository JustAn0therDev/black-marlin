#ifndef UTILCPP
#define UTILCPP

#include <cstdint>
#include <string>

struct Util
{
    // Writes a message to STDOUT, logs and ends the program's execution.
    static void Panic(const std::string& p_panic_message) noexcept;
};

#endif /* UTILCPP */
