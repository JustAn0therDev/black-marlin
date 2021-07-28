#include <string>

#ifndef LOGGERCPP
#define LOGGERCPP
constexpr char LOG_FILENAME[12] = "bm_logs.txt";

class Logger
{
public:
    static void Log(std::string p_message) noexcept;
private:
    static const std::string GetLogFileFullPath() noexcept;
};
#endif /* LOGGERCPP */
