#ifndef LOG_H
#define LOG_H

#include <string>

void logAlarm(const std::string& alarm);
void loadLoggedAlarms(const std::string& logFilePath);
void setLogFilePath(const std::string& path);
std::string getLogFilePath();

#endif // LOG_H
