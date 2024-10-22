cmake_minimum_required(VERSION 3.28)
project(TEST_PROJECT CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_library(Log)
target_sources(Log
    PUBLIC
        FILE_SET CXX_MODULES FILES
            Log/Log.cppm
)

add_executable(main main.cpp)

target_link_libraries(main Log)

