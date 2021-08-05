#ifndef LOGGERCPP
#define LOGGERCPP

#include <string>

constexpr char LOG_FILENAME[] = "bm_logs.txt";

class Logger
{
public:
    // Logs the message to the log file.
    static void Log(std::string p_message) noexcept;
private:
    // Returns the log's file full path.
    static const std::string GetLogFileFullPath() noexcept;
};

#endif /* LOGGERCPP */
