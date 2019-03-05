cmake_minimum_required(VERSION 3.12)

project(systemproxysetter)

set(CMAKE_CXX_STANDARD 14)

add_executable(systemproxysetter
        main.cpp
        src/proxysetting_win32.cpp
        src/proxysetting_darwin.cpp
        src/proxysetting_linux.cpp
        )