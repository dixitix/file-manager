cmake_minimum_required(VERSION 3.24)
project(file_manager)

set(CMAKE_CXX_STANDARD 17)

add_executable(file_manager main.cpp command_line.h file_system.h user_interface.h security.h testing.h command_line.cpp user_interface.cpp)
