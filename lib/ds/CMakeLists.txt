add_library(skunkwork.ds STATIC src/in_memory_lockless_queue.cpp)

target_include_directories(skunkwork.ds PUBLIC include/)
target_compile_features(skunkwork.ds PUBLIC cxx_std_20)
target_link_libraries(skunkwork.ds PUBLIC skunkwork.utils)
