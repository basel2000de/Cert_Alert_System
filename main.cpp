#include <iostream>
#include <sqlite3.h>
#include "db_init.h"
#include "db_operations.h"
#include "rss_parser.h"
#include <memory>

int main() {
    sqlite3* db;
    int exitCode = sqlite3_open("test.db", &db);

    // This automatically closes the database when it goes out of scope.
    std::unique_ptr<sqlite3, decltype(&sqlite3_close)> dbPtr(db, sqlite3_close);
    if (exitCode) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        // When an error occurs, the program should return a non-zero value to indicate failure.
        return 1;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    // Initialize the database
    initializeDatabase(db);

    // Clear previous keywords
    clearKeywords(db);

    // Add test keywords
    addKeyword(db, "GNOME");
    addKeyword(db, "ILIAS");

    // Fetch and print keywords for verification
    std::vector<std::string> keywords = fetchKeywords(db);
    std::cout << "Keywords in database:" << std::endl;
    for (const auto& keyword : keywords) {
        std::cout << keyword << std::endl;
    }

    // Parse the RSS feed
    auto rssFeedUrl = "https://wid.cert-bund.de/content/public/securityAdvisory/rss";
    parseRSSFeed(db, rssFeedUrl);

    return 0;
}
