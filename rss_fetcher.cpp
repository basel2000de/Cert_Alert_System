#include <string>
#include "rss_fetcher.h"
#include <cpr/cpr.h>

std::string fetchRSSFeed(const std::string& url) {

    cpr::Response r = cpr::Get(cpr::Url{url});


    return r.text;
}
