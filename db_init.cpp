#include <iostream>
#include <sqlite3.h>
#include "db_init.h"

void initializeDatabase(sqlite3* db) {
    char* errorMessage;
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Keywords (
            ID INTEGER PRIMARY KEY AUTOINCREMENT,
            Keyword TEXT NOT NULL
        );

        CREATE TABLE IF NOT EXISTS Advisories (
            ID INTEGER PRIMARY KEY AUTOINCREMENT,
            Title TEXT NOT NULL,
            Description TEXT NOT NULL,
            Link TEXT NOT NULL,
            Date TEXT NOT NULL,
            CVE_IDS TEXT,
            Keywords_Matched TEXT
        );
    )";

    int exit = sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "Error in initializing database: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        // Don't fail silently, throw an exception to indicate failure.
        throw std::runtime_error("Error in initializing database");
    } else {
        std::cout << "Database initialized successfully" << std::endl;
    }
}
