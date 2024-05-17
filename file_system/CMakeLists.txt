cmake_minimum_required(VERSION 3.27)
project(file_system)

set(CMAKE_CXX_STANDARD 17)

add_executable(file_system main.cpp
        source/filesystem.cpp
        commands/allcommands.cpp
)
