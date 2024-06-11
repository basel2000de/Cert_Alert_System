#ifndef STRPTIME_H
#define STRPTIME_H

#include <ctime>

tm* strptime(const char* s, const char* f, struct tm* tm);

#endif // STRPTIME_H
