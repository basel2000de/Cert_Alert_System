#include "log.h"
#include <fstream>
#include <iostream>
#include <set>

std::set<std::string> loggedAlarms;
std::string logFilePath = "alarms.log";

void setLogFilePath(const std::string& path) {
    logFilePath = path;
}

std::string getLogFilePath() {
    return logFilePath;
}

void loadLoggedAlarms(const std::string& logFilePath) {
    std::ifstream logFile(logFilePath);
    if (logFile.is_open()) {
        std::string line;
        while (std::getline(logFile, line)) {
            loggedAlarms.insert(line);
        }
        logFile.close();
    } else {
        std::cerr << "Error opening log file for reading: " << logFilePath << std::endl;
    }
}

void logAlarm(const std::string& alarm) {
    if (loggedAlarms.find(alarm) == loggedAlarms.end()) {
        std::ofstream logFile(logFilePath, std::ios::app);
        if (logFile.is_open()) {
            logFile << alarm << std::endl;
            logFile.close();
            loggedAlarms.insert(alarm);
        } else {
            std::cerr << "Error opening log file for writing: " << logFilePath << std::endl;
        }
    }
}
