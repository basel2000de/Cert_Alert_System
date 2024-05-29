#ifndef RSS_PARSER_H
#define RSS_PARSER_H

#include <sqlite3.h> // Include sqlite3
#include <string>

void parseRSSFeed(sqlite3* db, const std::string& url);

#endif // RSS_PARSER_H
