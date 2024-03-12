#include "logger/file_output.h"
#include <ctime>
#include "utils/datetime.h"

namespace logger {
FileOutput::FileOutput(std::string_view file_name, bool append_file_path)
{
    std::string log_file_path(file_name);
    if (append_file_path) {
        log_file_path += ("-" + datetime::get_formatted_current_date_time());
    }

    log_file_path += ".log";
    writer_.open(log_file_path.c_str(), std::ios::out | std::ios::app);
}

auto FileOutput::publish(std::string_view data) -> void
{
    writer_ << data << std::endl;
}

}  // namespace logger
