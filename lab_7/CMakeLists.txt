cmake_minimum_required(VERSION 3.10)
project(WarehouseManagementSystem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    Product.cpp
    FileOperations.cpp
    Menu.cpp
)

add_executable(WarehouseManagement ${SOURCES})

target_include_directories(WarehouseManagement PRIVATE .)