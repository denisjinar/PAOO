cmake_minimum_required(VERSION 3.16)
project(EffectiveCpp10To12 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(effective_cpp
    src/main.cpp
    src/Document.cpp
    src/Report.cpp
)

target_include_directories(effective_cpp PRIVATE include)

enable_testing()
add_test(NAME effective_cpp_items_10_12 COMMAND effective_cpp)