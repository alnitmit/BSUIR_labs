
cmake_minimum_required(VERSION 3.10.0)
project(lab_2 VERSION 0.1.0 LANGUAGES C CXX)

include_directories(include)

set(SOURCES 
    src/main.cpp
    src/String.cpp
)

set(HEADERS
    include/String.h
)

add_executable(lab2 ${SOURCES} ${HEADERS})