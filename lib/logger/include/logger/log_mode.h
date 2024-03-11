#pragma once

#include <string_view>

namespace logger {

enum class LogLevel
{
    Trace,
    Debug,
    Info,
    Warning,
    Error
};

[[nodiscard]] auto log_mode_to_string(LogLevel mode) -> std::string_view;

}  // namespace logger
