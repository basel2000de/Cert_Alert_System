#include <vector>
#include <string>
#include <sqlite3.h>
#include "db_operations.h"
#include <stdexcept>

std::vector<std::string> fetchKeywords(sqlite3 *db) {
    std::vector<std::string> keywords;
    sqlite3_stmt *stmt;

    auto sql = "SELECT Keyword FROM Keywords";

    bool preparation_result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK;
    if (!preparation_result) {
        throw std::runtime_error("Error in preparing statement in: " + std::string(__FUNCTION__));
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        auto keyword = sqlite3_column_text(stmt, 0);
        if (keyword) {
            keywords.emplace_back(reinterpret_cast<const char *>(keyword));
        }
    }

    sqlite3_finalize(stmt);
    return keywords;
}

void addKeyword(sqlite3 *db, const std::string &keyword) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO Keywords (Keyword) VALUES (?)";

    auto preparation_result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK;
    if (!preparation_result) {
        throw std::runtime_error("Error in preparing statement in: " + std::string(__FUNCTION__));
    }
    sqlite3_bind_text(stmt, 1, keyword.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void removeKeyword(sqlite3 *db, const std::string &keyword) {
    sqlite3_stmt *stmt;
    auto sql = "DELETE FROM Keywords WHERE Keyword = ?";

    bool preparation_result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK;
    if (!preparation_result) {
        throw std::runtime_error("Error in preparing statement in: " + std::string(__FUNCTION__));
    }
    sqlite3_bind_text(stmt, 1, keyword.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

}

void clearKeywords(sqlite3 *db) {
    auto sql = "DELETE FROM Keywords";
    sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
}
