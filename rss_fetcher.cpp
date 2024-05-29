#include <windows.h>
#include <wininet.h>
#include <string>
#include <sstream>
#include "rss_fetcher.h"

#pragma comment(lib, "wininet.lib")

std::string fetchRSSFeed(const std::string& url) {
    HINTERNET hInternet = InternetOpenA("RSSFeedFetcher", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) {
        return "";
    }

    HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        return "";
    }

    std::stringstream ss;
    char buffer[4096];
    DWORD bytesRead;
    while (InternetReadFile(hConnect, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead) {
        buffer[bytesRead] = '\0';
        ss << buffer;
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return ss.str();
}
