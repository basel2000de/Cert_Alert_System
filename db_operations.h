#ifndef DB_OPERATIONS_H
#define DB_OPERATIONS_H

#include <sqlite3.h>
#include <vector>
#include <string>

std::vector<std::string> fetchKeywords(sqlite3* db);
void addKeyword(sqlite3* db, const std::string& keyword);
void removeKeyword(sqlite3* db, const std::string& keyword);
void clearKeywords(sqlite3* db);

#endif // DB_OPERATIONS_H
