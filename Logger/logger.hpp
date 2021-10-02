#ifndef LOGGERCPP
#define LOGGERCPP

#include <string>
#include <fstream>
#include <ostream>
#include <stdio.h>

// The log filename to create/look for.
constexpr char LOG_FILENAME[] = "bm_logs.txt";
// The log message delimeter. This separates the normal message with the time the error occurred.
constexpr char LOG_MESSAGE_DELIMETER[] = " - ";
// The time message buffer's size. Since we don't always know the size of a key or value, this value will vary in future versions.
constexpr int TIME_BUFFER_SIZE = 100;

class Logger
{
    public:
        Logger();
        ~Logger();
        // Logs the message to the log file.
        void Log(const std::string& p_message) noexcept;
    private:
        // The "LOG_FILENAME"'s full path to allow writing.
        std::string m_full_filepath{};
        // The FILE* used to write to the log file.
        FILE* m_file;
};

#endif /* LOGGERCPP */
