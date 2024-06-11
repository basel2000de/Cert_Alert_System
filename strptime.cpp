#include "strptime.h"
#include <sstream>
#include <iomanip>
#include <cctype>

tm* strptime(const char* s, const char* f, struct tm* tm) {
    std::istringstream ss(s);
    ss >> std::get_time(tm, f);
    if (ss.fail()) {
        return nullptr;
    }
    return tm;
}
