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
    // Returns the log's file full path.
    static std::string GetLogFileFullPath() noexcept;
    // The stream for writing to the log file. It is set in this class' constructor
    std::ofstream m_log_file_writer;
};

#endif /* LOGGERCPP */
