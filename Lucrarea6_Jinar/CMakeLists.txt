cmake_minimum_required(VERSION 3.16)
project(EffectiveCpp13To14 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(effective_cpp
    src/main.cpp
    src/InputFile.cpp
    src/ShoppingCart.cpp
)

target_include_directories(effective_cpp PRIVATE include)

enable_testing()
add_test(NAME effective_cpp_items_13_14 COMMAND effective_cpp)
set_tests_properties(effective_cpp_items_13_14 PROPERTIES
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)