cmake_minimum_required(VERSION 3.10)
project(GeometricShapes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_executable(GeometricShapes ${SOURCES})

if(WIN32)
    target_compile_definitions(GeometricShapes PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()