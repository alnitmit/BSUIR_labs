cmake_minimum_required(VERSION 3.10)
project(StringDemoProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

find_package(PkgConfig)

add_executable(StringDemo
    main.cpp
    String.cpp
)

target_include_directories(StringDemo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(StringDemo PRIVATE cxx_std_17)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(StringDemo PRIVATE -Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(StringDemo PRIVATE /W4)
endif()

