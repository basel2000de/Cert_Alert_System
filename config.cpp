#include "config.h"
#include <fstream>
#include <iostream>
#include <sstream>

void saveEmailConfig(const EmailConfig& config) {
    std::ofstream configFile("email_config.ini");
    if (configFile.is_open()) {
        configFile << "activateEmail=" << (config.activateEmail ? "1" : "0") << std::endl;
        configFile << "smtpServer=" << config.smtpServer << std::endl;
        configFile << "smtpPort=" << config.smtpPort << std::endl;
        configFile << "emailAddress=" << config.emailAddress << std::endl;
        configFile << "emailPassword=" << config.emailPassword << std::endl;
        configFile.close();
    } else {
        std::cerr << "Error opening config file for writing." << std::endl;
    }
}

EmailConfig loadEmailConfig() {
    EmailConfig config;
    std::ifstream configFile("email_config.ini");
    if (configFile.is_open()) {
        std::string line;
        while (std::getline(configFile, line)) {
            std::istringstream is_line(line);
            std::string key;
            if (std::getline(is_line, key, '=')) {
                std::string value;
                if (std::getline(is_line, value)) {
                    if (key == "activateEmail") config.activateEmail = (value == "1");
                    else if (key == "smtpServer") config.smtpServer = value;
                    else if (key == "smtpPort") config.smtpPort = std::stoi(value);
                    else if (key == "emailAddress") config.emailAddress = value;
                    else if (key == "emailPassword") config.emailPassword = value;
                }
            }
        }
        configFile.close();
    } else {
        std::cerr << "Error opening config file for reading." << std::endl;
    }
    return config;
}

void saveAppConfig(const AppConfig& config) {
    std::ofstream configFile("app_config.ini");
    if (configFile.is_open()) {
        configFile << "rssLink=" << config.rssLink << std::endl;
        configFile << "lastRunDate=" << config.lastRunDate << std::endl;
        configFile.close();
    } else {
        std::cerr << "Error opening config file for writing." << std::endl;
    }
}

AppConfig loadAppConfig() {
    AppConfig config;
    std::ifstream configFile("app_config.ini");
    if (configFile.is_open()) {
        std::string line;
        while (std::getline(configFile, line)) {
            std::istringstream is_line(line);
            std::string key;
            if (std::getline(is_line, key, '=')) {
                std::string value;
                if (std::getline(is_line, value)) {
                    if (key == "rssLink") config.rssLink = value;
                    else if (key == "lastRunDate") config.lastRunDate = value;
                }
            }
        }
        configFile.close();
    } else {
        std::cerr << "Error opening config file for reading." << std::endl;
    }
    return config;
}
