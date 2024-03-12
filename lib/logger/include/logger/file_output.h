#pragma once

#include "logger/i_output.h"

#include <fstream>

namespace logger {

class FileOutput : public IOutput
{
   public:
    FileOutput(std::string_view file_name, bool append_file_path);

    ~FileOutput() = default;

    auto publish(std::string_view) -> void override;

   private:
    std::fstream writer_;
};

}  // namespace logger
