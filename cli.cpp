#include "cli.h"
#include "config.h"
#include "rss_fetcher.h"
#include "rss_parser.h"
#include "db_operations.h"
#include "log.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

void configureEmailSettings() {
    EmailConfig config;
    char activateEmail;

    std::cout << "Do you want to activate email notifications? (y/n): ";
    std::cin >> activateEmail;
    config.activateEmail = (activateEmail == 'y' || activateEmail == 'Y');

    if (config.activateEmail) {
        std::cout << "Enter SMTP server: ";
        std::cin >> config.smtpServer;
        std::cout << "Enter SMTP port: ";
        std::cin >> config.smtpPort;
        std::cout << "Enter your email address: ";
        std::cin >> config.emailAddress;
        std::cout << "Enter your email password: ";
        std::cin >> config.emailPassword;
    }

    saveEmailConfig(config);

    std::cout << "Email settings saved successfully." << std::endl;
}

void configureRSSLink() {
    AppConfig config = loadAppConfig();

    std::cout << "Enter the RSS feed URL: ";
    std::cin >> config.rssLink;

    saveAppConfig(config);

    std::cout << "RSS link saved successfully." << std::endl;
}

void configureLogFilePath() {
    std::string path;
    std::cout << "Enter the log file path: ";
    std::cin >> path;
    setLogFilePath(path);
    loadLoggedAlarms(path);  // Load alarms from the specified log file
    std::cout << "Log file path configured successfully." << std::endl;
}

void handleAddKeyword(sqlite3* db) {
    std::string keyword;
    std::cout << "Enter the keyword to add: ";
    std::cin >> keyword;

    addKeyword(db, keyword);

    std::cout << "Keyword added successfully." << std::endl;
}

void handleRemoveKeyword(sqlite3* db) {
    std::string keyword;
    std::cout << "Enter the keyword to remove: ";
    std::cin >> keyword;

    removeKeyword(db, keyword);

    std::cout << "Keyword removed successfully." << std::endl;
}

void handleListKeywords(sqlite3* db) {
    std::vector<std::string> keywords = fetchKeywords(db);
    std::cout << "Keywords:" << std::endl;
    for (const auto& keyword : keywords) {
        std::cout << "- " << keyword << std::endl;
    }
}

void handleParseRSSFeed(sqlite3* db) {
    AppConfig config = loadAppConfig();
    std::string url = config.rssLink;
    if (url.empty()) {
        std::cerr << "RSS link is not configured. Please configure it first." << std::endl;
        return;
    }

    std::string startDate;
    std::cout << "Enter the start date (YYYY-MM-DD) or type 'last' to use the last run date: ";
    std::cin >> startDate;

    if (startDate == "last") {
        startDate = config.lastRunDate;
        if (startDate.empty()) {
            std::cerr << "No last run date found. Please enter a valid date." << std::endl;
            return;
        }
    }

    parseRSSFeed(db, url, startDate);

    // Update last run date
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[11];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    config.lastRunDate = buffer;
    saveAppConfig(config);

    std::cout << "RSS feed parsed successfully." << std::endl;
}
