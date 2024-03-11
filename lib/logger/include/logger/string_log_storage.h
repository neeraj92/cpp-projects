#pragma once

#include <string>
#include <sstream>

namespace logger {

class StringLogStorage
{
   public:
    StringLogStorage() = default;
    StringLogStorage(std::string data) : data_(std::move(data))
    {
    }

    template <typename... Log>
    StringLogStorage(Log&&... logs)
    {
        std::stringstream sstr;
        ((sstr << logs << " "), ...);
        data_ = sstr.str();
    }

    auto to_string() const -> std::string
    {
        return data_;
    }

   private:
    std::string data_;
};

}  // namespace logger
