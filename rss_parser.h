#ifndef RSS_PARSER_H
#define RSS_PARSER_H

#include <sqlite3.h>
#include <string>
#include <windows.h>

void parseRSSFeed(sqlite3* db, const std::string& url);
void showNotification(const std::string& title, const std::string& message);
void sendEmailNotification(const std::string& subject, const std::string& body);

#endif // RSS_PARSER_H
