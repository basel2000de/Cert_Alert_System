#ifndef RSS_PARSER_H
#define RSS_PARSER_H

#include <sqlite3.h>
#include <string>
#include <vector>

bool containsKeyword(const std::string& text, const std::vector<std::string>& keywords, std::string& matchedKeyword);
void storeAdvisory(sqlite3* db, const std::string& title, const std::string& description, const std::string& link, const std::string& date, const std::string& cve_ids, const std::string& keywords_matched);
void parseRSSFeed(sqlite3* db, const std::string& url, const std::string& startDate);
void showNotification(const std::string& title, const std::string& message);
void sendEmailNotification(const std::string& subject, const std::string& body);

#endif // RSS_PARSER_H
