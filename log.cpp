#include "log.h"
#include <fstream>
#include <iostream>
#include <set>
#include <filesystem>

namespace fs = std::filesystem;

std::set<std::string> loggedAlarms;
std::string logFilePath = "alert_log.txt";

void setLogFilePath(const std::string& path) {
    logFilePath = path;
}

std::string getLogFilePath() {
    return logFilePath;
}

void loadLoggedAlarms(const std::string& logFilePath) {
    // Check if the log file exists, if not create it
    if (!fs::exists(logFilePath)) {
        std::ofstream logFile(logFilePath);
        if (!logFile.is_open()) {
            std::cerr << "Error creating log file: " << logFilePath << std::endl;
            return;
        }
        logFile.close();
    }

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
