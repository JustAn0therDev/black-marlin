#include <string>

#ifndef LOGGERCPP
#define LOGGERCPP
constexpr char LOG_FILENAME[12] = "bm_logs.txt";

class Logger
{
public:
    static void LogInfo(std::string p_message);
    static void LogWarning(std::string p_message);
    static void LogError(std::string p_message);
private:
    static const std::string GetLogFileFullPath();
};
#endif /* LOGGERCPP */
