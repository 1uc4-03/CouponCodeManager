#ifndef TIMEPARSER_H
#define TIMEPARSER_H

#include <chrono>

namespace ParseTime {

    std::chrono::system_clock::time_point createDateTime(int year,
                int month,
                int day,
                int hour,
                int minute,
                int second);

    time_t toUTC(std::tm& timeinfo);
    
}


#endif // TIMEPARSER_H