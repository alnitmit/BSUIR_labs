cmake_minimum_required(VERSION 3.10.0)
project(lab_2 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(lab2 
    src/main.cpp
    src/String.cpp
    include/String.h
)

target_compile_options(lab2 PRIVATE 
    $<$<CXX_COMPILER_ID:GNU>:-std=c++20>
    $<$<CXX_COMPILER_ID:Clang>:-std=c++20>
    $<$<CXX_COMPILER_ID:MSVC>:/std:c++20>
)