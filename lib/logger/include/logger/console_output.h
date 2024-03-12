#pragma once

#include "logger/i_output.h"

namespace logger {

class ConsoleOutput : public IOutput
{
   public:
    ~ConsoleOutput() = default;

    auto publish(std::string_view) -> void override;
};

}  // namespace logger
