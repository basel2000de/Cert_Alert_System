#include <iostream>
#include <pugixml.hpp>
#include <vector>
#include <string>
#include "rss_parser.h"
#include "rss_fetcher.h"
#include "db_operations.h"

bool containsKeyword(const std::string& text, const std::vector<std::string>& keywords, std::string& matchedKeyword) {
    for (const auto& keyword : keywords) {
        if (text.find(keyword) != std::string::npos) {
            matchedKeyword = keyword;
            return true;
        }
    }
    return false;
}

void parseRSSFeed(sqlite3* db, const std::string& url) {
    std::string rssContent = fetchRSSFeed(url);

    if (rssContent.empty()) {
        std::cerr << "Error: could not fetch RSS feed from URL " << url << std::endl;
        return;
    }

    std::vector<std::string> keywords = fetchKeywords(db);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(rssContent.c_str());

    if (!result) {
        std::cerr << "Error: could not parse RSS feed" << std::endl;
        return;
    }

    pugi::xml_node channel = doc.child("rss").child("channel");
    for (pugi::xml_node item = channel.child("item"); item; item = item.next_sibling("item")) {
        std::string title = item.child_value("title");
        std::string description = item.child_value("description");
        std::string matchedKeyword;

        if (containsKeyword(title, keywords, matchedKeyword) || containsKeyword(description, keywords, matchedKeyword)) {
            std::cout << "Title: " << title << std::endl;
            std::cout << "Link: " << item.child_value("link") << std::endl;
            std::cout << "Description: " << description << std::endl;
            std::cout << "Date: " << item.child_value("pubDate") << std::endl;
            std::cout << "Matched Keyword: " << matchedKeyword << std::endl;
        }
    }
}
