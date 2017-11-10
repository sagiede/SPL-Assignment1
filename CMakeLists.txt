cmake_minimum_required(VERSION 3.8)
project(assignment1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/Commands.cpp src/Environment.cpp src/Files.cpp src/FileSystem.cpp src/Main.cpp)
add_executable(assignment1 ${SOURCE_FILES})