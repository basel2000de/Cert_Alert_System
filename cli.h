#ifndef CLI_H
#define CLI_H

#include <sqlite3.h>

void configureEmailSettings();
void configureRSSLink();
void configureLogFilePath();
void handleAddKeyword(sqlite3* db);
void handleRemoveKeyword(sqlite3* db);
void handleListKeywords(sqlite3* db);
void handleParseRSSFeed(sqlite3* db);

#endif // CLI_H
