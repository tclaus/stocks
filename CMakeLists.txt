cmake_minimum_required(VERSION 3.23)

project(Stocks)

set(CMAKE_MODULE_PATH "${Stocks_SOURCE_DIR}/CMakeModules")

include(UseHaiku)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED False) # Set to true once we know better what to do

add_executable(${PROJECT_NAME} App.cpp)
target_include_directories( ${PROJECT_NAME} SYSTEM PUBLIC
        headers/config
        headers/os
        headers/os/add-ons/graphics
        headers/os/app
        headers/os/interface
        headers/os/kernel
        headers/os/locale
        headers/os/storage
        headers/posix
        headers/os/support
        )

add_subdirectory(gui)

#target_link_libraries(${PROJECT_NAME} "be" "tracker" "stdc++" )