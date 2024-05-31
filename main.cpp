#include <iostream>
#include <sqlite3.h>
#include "db_init.h"
#include "cli.h"
#include "ini.h" // You can use an INI parsing library like inih

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

    // Load email settings from config file
    mINI::INIFile file("config.ini");
    mINI::INIStructure ini;
    if (file.read(ini)) {
        std::string recipientEmail = ini["EmailSettings"]["recipient_email"];
        std::string recipientName = ini["EmailSettings"]["recipient_name"];
    }

    int choice;
    do {
        displayMenu();
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cerr << "Invalid input. Please enter a number." << std::endl;
            displayMenu();
        }

        switch (choice) {
            case 1:
                handleAddKeyword(db);
            break;
            case 2:
                handleRemoveKeyword(db);
            break;
            case 3:
                handleListKeywords(db);
            break;
            case 4:
                handleParseRSSFeed(db);
            break;
            case 5:
                configureEmailSettings(db);
            break;
            case 6:
                std::cout << "Exiting..." << std::endl;
            break;
            default:
                std::cerr << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 6);

    sqlite3_close(db);
    return 0;
}
