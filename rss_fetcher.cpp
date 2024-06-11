#include "rss_fetcher.h"
#include <windows.h>
#include <wininet.h>
#include <string>
#include <iostream>

std::string fetchRSSFeed(const std::string& url) {
    HINTERNET hInternet = InternetOpenA("RSSFeedFetcher", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) {
        std::cerr << "Error: InternetOpenA failed." << std::endl;
        return "";
    }

    HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) {
        std::cerr << "Error: InternetOpenUrlA failed." << std::endl;
        InternetCloseHandle(hInternet);
        return "";
    }

    char buffer[4096];
    DWORD bytesRead;
    std::string content;

    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        content.append(buffer, bytesRead);
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return content;
}
