cmake_minimum_required(VERSION 3.10)
project(TemaCpp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DEMO_DOUBLE_FREE "Rulează demo-ul care produce double free" OFF)

add_executable(tema
    src/main.cpp
    src/Playlist.cpp
    src/BadPlaylist.cpp
)

target_include_directories(tema PRIVATE ${CMAKE_SOURCE_DIR}/include)
if(MSVC)
    target_compile_options(tema PRIVATE /W4)
else()
    target_compile_options(tema PRIVATE -Wall -Wextra)
endif()

if(DEMO_DOUBLE_FREE)
    target_compile_definitions(tema PRIVATE DEMO_DOUBLE_FREE)
endif()