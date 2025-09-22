
cmake_minimum_required(VERSION 3.10.0)
project(lab_1 VERSION 0.1.0 LANGUAGES C CXX)

include_directories(include)

set(SOURCES 
    src/main.cpp
    src/Matrix.cpp
)

set(HEADERS
    include/Matrix.h
)

add_executable(lab1 ${SOURCES} ${HEADERS})