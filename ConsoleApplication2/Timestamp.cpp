#include "Timestamp.h"
#include <time.h>       /* time_t, struct tm, time, localtime, strftime */


std::string GetCurrentTimestamp() {
    time_t rawtime;
    struct tm* timeinfo;
    const int maxLen = 80;
    char buffer[maxLen];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, maxLen, "%c", timeinfo);
    std::string output = buffer;
    return output;
}