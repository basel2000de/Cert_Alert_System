#include <iostream>
#include <sqlite3.h>
#include "db_init.h"
#include "db_operations.h"
#include "rss_parser.h"

int main() {
    sqlite3* db;
    int exit = sqlite3_open("test.db", &db);

    if (exit) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 0;
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
    std::string rssFeedUrl = "https://wid.cert-bund.de/content/public/securityAdvisory/rss";
    parseRSSFeed(db, rssFeedUrl);

    sqlite3_close(db);
    return 0;
}
