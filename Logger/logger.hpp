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
// The size of the log message.
// A key can easily exceed more than 200 characters considering it will almost always be some kind of big string or JSON structure.
constexpr int LOG_MESSAGE_SIZE = 600;
// The time message buffer's size. The size of the formatted time string including the size of the log message.
constexpr int TIME_STRING_SIZE = LOG_MESSAGE_SIZE + 20;


class Logger
{
    public:
        Logger();
        ~Logger();
        // Logs the message to the log file.
        void Log(const char* p_message) noexcept;
    private:
        // The "LOG_FILENAME"'s full path to allow writing.
        std::string m_full_filepath{};
        // The FILE* used to write to the log file.
        FILE* m_file;
};

#endif /* LOGGERCPP */
