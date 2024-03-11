#include "logger/log_mode.h"

namespace logger {

auto log_mode_to_string(LogLevel mode) -> std::string_view
{
    using enum LogLevel;

    switch (mode) {
        case Trace:
            return "TRACE";
        case Debug:
            return "DEBUG";
        case Info:
            return "INFO";
        case Warning:
            return "WARNING";
        case Error:
            return "ERROR";
    }
    return "TRACE";
}

}  // namespace logger
