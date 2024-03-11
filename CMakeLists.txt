cmake_minimum_required(VERSION 3.22)

project(skunkworks)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_subdirectory(lib)
add_subdirectory(apps)


enable_testing()
add_subdirectory(test)
