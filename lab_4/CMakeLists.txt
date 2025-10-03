
cmake_minimum_required(VERSION 3.10.0)
project(lab_4 VERSION 0.1.0 LANGUAGES C CXX)

include_directories(include)

set(SOURCES 
    src/main.cpp
)

set(HEADERS

)

add_executable(lab4 ${SOURCES} ${HEADERS})