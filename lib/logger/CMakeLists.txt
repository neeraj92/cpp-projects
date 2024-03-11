add_library(skunkwork.logger src/log_mode.cpp src/logger.cpp src/string_log_storage.cpp)

target_include_directories(skunkwork.logger PUBLIC include)
target_link_libraries(skunkwork.logger PUBLIC skunkwork.ds)
