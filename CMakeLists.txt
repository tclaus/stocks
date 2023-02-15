cmake_minimum_required(VERSION 3.23)

project(Stocks)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED False) # Set to true once we know better what to do

add_executable(${PROJECT_NAME} App.cpp)
target_include_directories( ${PROJECT_NAME} SYSTEM PUBLIC
        /Users/thorstenclaus/haiku-dev/haiku/headers/config
        /Users/thorstenclaus/haiku-dev/haiku/headers/posix
        /Users/thorstenclaus/haiku-dev/haiku/headers/os
        /Users/thorstenclaus/haiku-dev/haiku/headers/os/app
        /Users/thorstenclaus/haiku-dev/haiku/headers/os/interface
        /Users/thorstenclaus/haiku-dev/haiku/headers/os/kernel
        /Users/thorstenclaus/haiku-dev/haiku/headers/os/locale
        /Users/thorstenclaus/haiku-dev/haiku/headers/os/storage
        /Users/thorstenclaus/haiku-dev/haiku/headers/os/support
        )

add_subdirectory(gui)

