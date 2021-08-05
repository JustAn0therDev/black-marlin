#ifndef LOGGERCPP
#define LOGGERCPP

#include <string>

constexpr char LOG_FILENAME[] = "bm_logs.txt";

class Logger
{
public:
    static void Log(std::string p_message) noexcept;
private:
    static const std::string GetLogFileFullPath() noexcept;
};

#endif /* LOGGERCPP */
