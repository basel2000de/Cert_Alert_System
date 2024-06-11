#include <iostream>
#include <sqlite3.h>
#include "cli.h"
#include "db_init.h"
#include "config.h"
#include "log.h"

int main() {
    sqlite3* db;
    int exit = sqlite3_open("keywords.db", &db);
    if (exit) {
        std::cerr << "Error opening DB: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    initializeDatabase(db);

    char choice;
    while (true) {
        std::cout << "\nCERT Alert System Menu:\n";
        std::cout << "1. Configure Email Settings\n";
        std::cout << "2. Configure RSS Link\n";
        std::cout << "3. Configure Log File Path\n";  // New option for log file path
        std::cout << "4. Add Keyword\n";
        std::cout << "5. Remove Keyword\n";
        std::cout << "6. List Keywords\n";
        std::cout << "7. Parse RSS Feed\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                configureEmailSettings();
            break;
            case '2':
                configureRSSLink();
            break;
            case '3':
                configureLogFilePath();  // Handle log file path configuration
            break;
            case '4':
                handleAddKeyword(db);
            break;
            case '5':
                handleRemoveKeyword(db);
            break;
            case '6':
                handleListKeywords(db);
            break;
            case '7':
                handleParseRSSFeed(db);
            break;
            case '8':
                sqlite3_close(db);
            return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    sqlite3_close(db);
    return 0;
}
