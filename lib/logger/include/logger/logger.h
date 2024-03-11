#pragma once

#include "logger/log_mode.h"

#include "ds/in_memory_lockless_queue.h"
#include "logger/string_log_storage.h"

#include <cstdint>
#include <source_location>
#include <stop_token>
#include <thread>

namespace logger {

template <typename T>
struct LogElement
{
    uint64_t timestamp{};
    T data;
    LogLevel level{};
    std::source_location location{};

    LogElement() = default;
    LogElement(const T &data, LogLevel level, const std::source_location &location);
    LogElement(T &&data, LogLevel level, const std::source_location &location);
};

template <typename T>
class Formatter
{
   public:
    auto enqueue(LogLevel level, T &&data, const std::source_location &location) -> void;
    auto enqueue(LogLevel level, const T &data, const std::source_location &location) -> void;
    auto is_smallest(uint64_t &current_smallest) -> void;

    auto log_line_if_smallest(uint64_t smallest, std::string &print_string) -> void;

   private:
    ds::InMemoryLocklessQueue<LogElement<T>> storage_{10000};
    uint64_t front_timestamp_{};
};

template <typename... TypesToLog>
class Logger : public Formatter<StringLogStorage>, public Formatter<TypesToLog>...
{
   public:
    Logger(LogLevel level);
    ~Logger();

    template <typename Log>
    auto log(LogLevel level, Log &&to_log, std::source_location location = std::source_location::current()) -> void;

   private:
    auto run(const std::stop_token &token) -> void;
    [[nodiscard]] auto print_log() -> bool;
    LogLevel level_{LogLevel::Trace};
    std::jthread runner_;
};

}  // namespace logger

#include "logger/logger.hpp"
