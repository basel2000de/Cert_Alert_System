#include "rss_parser.h"
#include <iostream>
#include <pugixml.hpp>
#include <vector>
#include <string>
#include "rss_fetcher.h"
#include "db_operations.h"
#include "SMTPClient.h"
#include "MAILClient.h"
#include "CurlHandle.h"
#include <fstream>

using namespace jed_utils;

bool containsKeyword(const std::string& text, const std::vector<std::string>& keywords, std::string& matchedKeyword) {
    for (const auto& keyword : keywords) {
        if (text.find(keyword) != std::string::npos) {
            matchedKeyword = keyword;
            return true;
        }
    }
    return false;
}

void storeAdvisory(sqlite3* db, const std::string& title, const std::string& description, const std::string& link, const std::string& date, const std::string& cve_ids, const std::string& keywords_matched) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO Advisories (Title, Description, Link, Date, CVE_IDS, Keywords_Matched) VALUES (?, ?, ?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, description.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, link.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, date.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, cve_ids.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, keywords_matched.c_str(), -1, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void showNotification(const std::string& title, const std::string& message) {
    MessageBoxA(NULL, message.c_str(), title.c_str(), MB_OK | MB_ICONINFORMATION);
}

void sendEmailNotification(const std::string& subject, const std::string& body) {
    // Load email configuration
    std::ifstream configFile("email_config.ini");
    std::string smtpServer, smtpPort, emailAddress, emailPassword;
    if (configFile.is_open()) {
        std::string line;
        while (std::getline(configFile, line)) {
            size_t pos = line.find("=");
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            if (key == "smtpServer") smtpServer = value;
            else if (key == "smtpPort") smtpPort = value;
            else if (key == "emailAddress") emailAddress = value;
            else if (key == "emailPassword") emailPassword = value;
        }
        configFile.close();
    }

    // Prepare email
    EmailAddress sender(emailAddress.c_str(), "Sender");
    EmailAddress recipient(emailAddress.c_str(), "Recipient"); // For testing, send to the same address
    MimeMessage message(&sender, "CERT Alert", body.c_str(), MimeMessage::TEXT_HTML);
    message.addRecipient(&recipient);

    // Set SMTP server and send email
    SmtpClient smtp(smtpServer.c_str(), std::stoi(smtpPort));
    smtp.setCredentials(emailAddress.c_str(), emailPassword.c_str());
    smtp.sendMail(message);
}

void parseRSSFeed(sqlite3* db, const std::string& url) {
    std::string rssContent = fetchRSSFeed(url);

    if (rssContent.empty()) {
        std::cerr << "Error: could not fetch RSS feed from URL " << url << std::endl;
        return;
    }

    std::vector<std::string> keywords = fetchKeywords(db);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(rssContent.c_str());

    if (!result) {
        std::cerr << "Error: could not parse RSS feed" << std::endl;
        return;
    }

    pugi::xml_node channel = doc.child("rss").child("channel");
    for (pugi::xml_node item = channel.child("item"); item; item = item.next_sibling("item")) {
        std::string title = item.child_value("title");
        std::string description = item.child_value("description");
        std::string link = item.child_value("link");
        std::string date = item.child_value("pubDate");
        std::string matchedKeyword;

        if (containsKeyword(title, keywords, matchedKeyword) || containsKeyword(description, keywords, matchedKeyword)) {
            std::cout << "Title: " << title << std::endl;
            std::cout << "Link: " << link << std::endl;
            std::cout << "Description: " << description << std::endl;
            std::cout << "Date: " << date << std::endl;
            std::cout << "Matched Keyword: " << matchedKeyword << std::endl;

            storeAdvisory(db, title, description, link, date, "", matchedKeyword);
            showNotification(title, description);
            sendEmailNotification(title, description);
        }
    }
}
