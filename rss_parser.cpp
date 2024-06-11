#include "rss_parser.h"
#include "rss_fetcher.h"
#include "db_operations.h"
#include "strptime.h"  // Include custom strptime header
#include <pugixml.hpp>
#include <iostream>
#include <windows.h>
#include <mapi.h>
#include <ctime>

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
    } else {
        std::cerr << "Error storing advisory: " << sqlite3_errmsg(db) << std::endl;
    }
}

void parseRSSFeed(sqlite3* db, const std::string& url, const std::string& startDate) {
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

        struct tm tm;
        strptime(date.c_str(), "%a, %d %b %Y %H:%M:%S %Z", &tm);
        time_t itemTime = mktime(&tm);
        strptime(startDate.c_str(), "%Y-%m-%d", &tm);
        time_t startTime = mktime(&tm);

        if (difftime(itemTime, startTime) < 0) {
            continue;
        }

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

void showNotification(const std::string& title, const std::string& message) {
    MessageBoxA(NULL, message.c_str(), title.c_str(), MB_OK | MB_ICONINFORMATION);
}

void sendEmailNotification(const std::string& subject, const std::string& body) {
    HINSTANCE hMapi = LoadLibraryA("MAPI32.DLL");
    if (!hMapi) {
        std::cerr << "MAPI library not found." << std::endl;
        return;
    }

    LPMAPISENDMAIL lpfnMAPISendMail = (LPMAPISENDMAIL)GetProcAddress(hMapi, "MAPISendMail");
    if (!lpfnMAPISendMail) {
        std::cerr << "MAPISendMail not found." << std::endl;
        FreeLibrary(hMapi);
        return;
    }

    MapiMessage message = { 0 };
    MapiRecipDesc recipient = { 0 };
    recipient.ulRecipClass = MAPI_TO;
    recipient.lpszAddress = const_cast<char*>("mailto:your-email@example.com");
    recipient.lpszName = const_cast<char*>("Recipient Name");

    message.lpszSubject = const_cast<char*>(subject.c_str());
    message.lpszNoteText = const_cast<char*>(body.c_str());
    message.nRecipCount = 1;
    message.lpRecips = &recipient;

    if (lpfnMAPISendMail(0, 0, &message, MAPI_LOGON_UI | MAPI_DIALOG, 0) != SUCCESS_SUCCESS) {
        std::cerr << "Failed to send email." << std::endl;
    }

    FreeLibrary(hMapi);
}
