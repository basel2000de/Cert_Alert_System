#include "cli.h"
#include <iostream>
#include <vector>
#include <string>
#include "db_operations.h"
#include "rss_parser.h"
#include <fstream>

void displayMenu() {
    std::cout << "1. Add keyword" << std::endl;
    std::cout << "2. Remove keyword" << std::endl;
    std::cout << "3. List keywords" << std::endl;
    std::cout << "4. Parse RSS feed" << std::endl;
    std::cout << "5. Configure email settings" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}


void handleAddKeyword(sqlite3* db) {
    std::string keyword;
    std::cout << "Enter keyword to add: ";
    std::cin >> keyword;
    if (!keyword.empty()) {
        addKeyword(db, keyword);
        std::cout << "Keyword added successfully." << std::endl;
    } else {
        std::cerr << "Keyword cannot be empty." << std::endl;
    }
}

void handleRemoveKeyword(sqlite3* db) {
    std::string keyword;
    std::cout << "Enter keyword to remove: ";
    std::cin >> keyword;
    if (!keyword.empty()) {
        removeKeyword(db, keyword);
        std::cout << "Keyword removed successfully." << std::endl;
    } else {
        std::cerr << "Keyword cannot be empty." << std::endl;
    }
}

void handleListKeywords(sqlite3* db) {
    std::vector<std::string> keywords = fetchKeywords(db);
    if (keywords.empty()) {
        std::cout << "No keywords in database." << std::endl;
    } else {
        std::cout << "Keywords in database:" << std::endl;
        for (const auto& keyword : keywords) {
            std::cout << keyword << std::endl;
        }
    }
}

void handleParseRSSFeed(sqlite3* db) {
    std::string rssFeedUrl = "https://wid.cert-bund.de/content/public/securityAdvisory/rss";
    parseRSSFeed(db, rssFeedUrl);
}

void configureEmailSettings() {
    std::string smtpServer, smtpPort, emailAddress, emailPassword;
    std::cout << "Enter SMTP server: ";
    std::cin >> smtpServer;
    std::cout << "Enter SMTP port: ";
    std::cin >> smtpPort;
    std::cout << "Enter your email address: ";
    std::cin >> emailAddress;
    std::cout << "Enter your email password: ";
    std::cin >> emailPassword;

    // Save to config file
    std::ofstream configFile("email_config.ini");
    configFile << "smtpServer=" << smtpServer << std::endl;
    configFile << "smtpPort=" << smtpPort << std::endl;
    configFile << "emailAddress=" << emailAddress << std::endl;
    configFile << "emailPassword=" << emailPassword << std::endl;
    configFile.close();

    std::cout << "Email settings saved successfully." << std::endl;
}
