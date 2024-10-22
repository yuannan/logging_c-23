cmake_minimum_required(VERSION 3.28)
project(SPLLOG CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

add_library(Constants)
target_sources(Constants
    PUBLIC
        FILE_SET CXX_MODULES FILES
            Constants/Constants.cppm
            Constants/SplLog.cppm
)

add_library(Log)
target_sources(Log
    PUBLIC
        FILE_SET CXX_MODULES FILES
            Log/Log.cppm
)

add_executable(SplLog main.cpp)

target_link_libraries(SplLog Log)
target_link_libraries(Log Constants)
