cmake_minimum_required(VERSION 3.10)
project(BinaryTreeLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

add_executable(BinaryTree
    src/main.cpp
    src/Tree.cpp
    src/TreeIterator.cpp
    src/TreeAlgorithm.cpp
)

target_include_directories(BinaryTree PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(BinaryTree PRIVATE cxx_std_17)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(BinaryTree PRIVATE -Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(BinaryTree PRIVATE /W4)
endif()