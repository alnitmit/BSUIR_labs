
cmake_minimum_required(VERSION 3.10.0)
project(lab_4 VERSION 0.1.0 LANGUAGES C CXX)

include_directories(include)

set(SOURCES 
    src/main.cpp
    src/Circle.cpp
    src/Rectangle.cpp
    src/Triangle.cpp
    src/Sphere.cpp
    src/Cube.cpp
    src/Cylinder.cpp
)

set(HEADERS
    include/Shape.h
    include/Circle.h
    include/Rectangle.h
    include/Triangle.h
    include/Sphere.h
    include/Cube.h
    include/Cylinder.h
)

add_executable(lab4 ${SOURCES} ${HEADERS})