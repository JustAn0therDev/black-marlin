#ifndef LOGGERCPP
#define LOGGERCPP

#include <string>
#include <fstream>
#include <ostream>

constexpr char LOG_FILENAME[] = "bm_logs.txt";

class Logger
{
public:
    Logger();
    // Logs the message to the log file.
    void Log(const std::string& p_message) noexcept;
private:
    // The "LOG_FILENAME" stream so writing is possible.
    std::string m_full_filepath;
};

#endif /* LOGGERCPP */
