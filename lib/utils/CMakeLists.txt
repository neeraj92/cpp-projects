add_library(skunkwork.utils STATIC src/math.cpp src/datetime.cpp)

target_include_directories(skunkwork.utils PUBLIC include/)
target_compile_features(skunkwork.utils PUBLIC cxx_std_20)
