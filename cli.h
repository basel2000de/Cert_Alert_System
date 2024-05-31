#ifndef CLI_H
#define CLI_H

#include <sqlite3.h>

void displayMenu();
void handleAddKeyword(sqlite3* db);
void handleRemoveKeyword(sqlite3* db);
void handleListKeywords(sqlite3* db);
void handleParseRSSFeed(sqlite3* db);
void configureEmailSettings(sqlite3* db);
void configureEmailSettings();


#endif // CLI_H
