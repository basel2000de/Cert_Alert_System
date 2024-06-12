#include <iostream>
#include <sqlite3.h>
#include "cli.h"
#include "db_init.h"
#include "config.h"
#include "log.h"
#include <thread>

int main() {
    sqlite3* db;
    int exit = sqlite3_open("keywords.db", &db);
    if (exit) {
        std::cerr << "Error opening DB: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    initializeDatabase(db);
    std::string defaultLogFilePath = "alert_log.txt";
    setLogFilePath(defaultLogFilePath);
    loadLoggedAlarms(getLogFilePath());  // Load logged alarms to avoid duplicates

    char choice;
    bool autoRun = false;
    std::thread autoRunThread;

    while (true) {
        std::cout << "\nCERT Alert System Menu:\n";
        std::cout << "1. Configure Email Settings\n";
        std::cout << "2. Configure RSS Link\n";
        std::cout << "3. Configure Log File Path\n";
        std::cout << "4. Configure Interval for Auto Run\n";
        std::cout << "5. Add Keyword\n";
        std::cout << "6. Remove Keyword\n";
        std::cout << "7. List Keywords\n";
        std::cout << "8. Parse RSS Feed\n";
        std::cout << "9. Enable/Disable Auto Run\n";
        std::cout << "0. Exit\n";
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
                configureLogFilePath();
                break;
            case '4':
                configureInterval();
                break;
            case '5':
                handleAddKeyword(db);
                break;
            case '6':
                handleRemoveKeyword(db);
                break;
            case '7':
                handleListKeywords(db);
                break;
            case '8':
                handleParseRSSFeed(db);
                break;
            case '9':
                autoRun = !autoRun;
                if (autoRun) {
                    std::cout << "Auto Run enabled." << std::endl;
                    autoRunThread = std::thread(autoRunParser, db);
                    autoRunThread.detach();
                } else {
                    std::cout << "Auto Run disabled." << std::endl;
                    // Optionally, implement a way to stop the thread gracefully
                }
                break;
            case '0':
                sqlite3_close(db);
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    sqlite3_close(db);
    return 0;
}
