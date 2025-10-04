cmake_minimum_required(VERSION 3.10)
project(BinaryTreeCalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BinaryTreeCalculator
    main.cpp
    ExpressiomTree.cpp
)

if(WIN32)
    target_compile_definitions(BinaryTreeCalculator PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()