#pragma once

#include <string_view>

namespace logger {

class IOutput
{
   public:
    virtual ~IOutput() = default;

    virtual auto publish(std::string_view) -> void = 0;
};

}  // namespace logger
