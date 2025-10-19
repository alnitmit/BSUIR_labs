cmake_minimum_required(VERSION 3.10)
project(WarehouseManagementSystem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(WarehouseManagement
    src/main.cpp
    src/Product.cpp
    src/FileOperations.cpp
    src/Menu.cpp
)

target_include_directories(WarehouseManagement PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(WarehouseManagement PRIVATE -Wall -Wextra)
endif()