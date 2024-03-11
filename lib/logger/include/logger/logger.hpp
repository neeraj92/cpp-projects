#pragma once

#include "logger/log_mode.h"
#include "logger/logger.h"

#include "logger/string_log_storage.h"
#include "utils/datetime.h"

#include <filesystem>
#include <iostream>
#include <limits>
#include <source_location>
#include <sstream>
#include <stop_token>
#include <thread>

namespace logger {

template <typename T>
LogElement<T>::LogElement(const T &_data, LogLevel _level, const std::source_location &_location)
    : timestamp(datetime::get_current_time_rt()), level(_level), location(_location)
{
    data = _data;
}

template <typename T>
LogElement<T>::LogElement(T &&_data, LogLevel _level, const std::source_location &_location)
    : timestamp(datetime::get_current_time_rt()), level(_level), location(_location)
{
    data = std::move(_data);
}

template <typename T>
auto Formatter<T>::enqueue(LogLevel level, T &&data, const std::source_location &location) -> void
{
    LogElement<T> element(data, level, location);
    storage_.enqueue(std::move(element));
}

template <typename T>
auto Formatter<T>::enqueue(LogLevel level, const T &data, const std::source_location &location) -> void
{
    LogElement<T> element(data, level, location);
    storage_.enqueue(std::move(element));
}

template <typename T>
auto Formatter<T>::is_smallest(uint64_t &smallest) -> void
{
    if (storage_.empty()) {
        return;
    }

    auto front = storage_.front();

    if (front->timestamp < smallest) {
        smallest = front->timestamp;
        front_timestamp_ = front->timestamp;
    }
}

template <typename T>
auto Formatter<T>::log_line_if_smallest(uint64_t smallest, std::string &print_string) -> void
{
    if (front_timestamp_ == smallest) {
        auto element = storage_.dequeue();
        front_timestamp_ = 0;
        std::stringstream sstr;
        std::filesystem::path file_path(element->location.file_name());
        sstr << datetime::convert_epoch_to_string(element->timestamp) << " [" << log_mode_to_string(element->level)
             << "] " << std::string(file_path.filename()) << ":" << element->location.line() << " "
             << element->data.to_string();
        print_string = sstr.str();
    }
}

template <typename... TypesToLog>
Logger<TypesToLog...>::Logger(LogLevel level) : level_(level)
{
    runner_ = std::jthread([this](const std::stop_token &token) { run(token); });
}

template <typename... TypesToLog>
template <typename Log>
auto Logger<TypesToLog...>::log(LogLevel level, Log &&to_log, std::source_location location) -> void
{
    using T = std::decay_t<Log>;
    if (static_cast<int>(level) >= static_cast<int>(level_)) {
        static_cast<Formatter<T> *>(this)->enqueue(level, std::forward<Log>(to_log), location);
    }
}

template <typename... TypesToLog>
auto Logger<TypesToLog...>::run(const std::stop_token &token) -> void
{
    while (!token.stop_requested()) {
        std::ignore = print_log();
        std::this_thread::yield();
    }

    while (print_log());
}

template <typename... TypesToLog>
auto Logger<TypesToLog...>::print_log() -> bool
{
    constexpr auto max_timestamp = std::numeric_limits<uint64_t>::max();
    uint64_t smallest_timestamp = max_timestamp;

    (static_cast<Formatter<TypesToLog> *>(this)->is_smallest(smallest_timestamp), ...);
    static_cast<Formatter<StringLogStorage> *>(this)->is_smallest(smallest_timestamp);

    if (smallest_timestamp != max_timestamp) {
        std::string to_publish{};

        (static_cast<Formatter<TypesToLog> *>(this)->log_line_if_smallest(smallest_timestamp, to_publish), ...);
        static_cast<Formatter<StringLogStorage> *>(this)->log_line_if_smallest(smallest_timestamp, to_publish);
        std::cout << to_publish << std::endl;
        return true;
    }

    return false;
}

template <typename... TypesToLog>
Logger<TypesToLog...>::~Logger()
{
    runner_.request_stop();
}

}  // namespace logger
