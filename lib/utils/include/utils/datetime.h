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

inline auto convert_epoch_to_string(uint64_t intime) -> std::string
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

inline auto get_formatted_current_date_time() -> std::string
{
    time_t t = time(NULL);
    auto local_time = localtime(&t);

    auto format = "%04d%02d%02d-%02d%02d%02d";

    char output_buffer[50];
    sprintf(
        output_buffer, format, local_time->tm_year + 1900, local_time->tm_mon, local_time->tm_mday, local_time->tm_hour,
        local_time->tm_min, local_time->tm_sec);
    return output_buffer;
}

}  // namespace datetime
