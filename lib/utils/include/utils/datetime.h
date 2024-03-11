#pragma once

#include <ctime>
#include <cstdint>
#include <time.h>
#include <ratio>
#include <string>
#include <cstring>

namespace datetime {

inline auto get_current_time_rt() -> uint64_t
{
    struct timespec timespec;
    clock_gettime(CLOCK_REALTIME, &timespec);
    return timespec.tv_sec * std::nano::den + timespec.tv_nsec;
}

inline std::string convert_epoch_to_string(uint64_t intime)
{
    char print_buffer[50];
    memset(print_buffer, '\0', sizeof(print_buffer));

    std::string s_format = "%4d%02d%02d-%02d:%02d:%02d.%09d";
    int nanoseconds = intime % std::nano::den;
    time_t epoch = static_cast<time_t>(intime) / std::nano::den;

    struct tm time;
    localtime_r(&epoch, &time);
    sprintf(
        print_buffer, s_format.c_str(), time.tm_year + 1900, time.tm_mon + 1, time.tm_mday, time.tm_hour, time.tm_min,
        time.tm_sec, nanoseconds);
    return std::string(print_buffer);
}

}  // namespace datetime
