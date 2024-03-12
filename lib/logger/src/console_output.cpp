#include "logger/console_output.h"

#include <iostream>

namespace logger {

auto ConsoleOutput::publish(std::string_view data) -> void
{
    std::cout << data << std::endl;
}

}  // namespace logger
