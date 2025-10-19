cmake_minimum_required(VERSION 3.10)
project(WarehouseManagementSystem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем все предупреждения и отладочную информацию
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

add_executable(WarehouseManagement
    main.cpp
    Product.cpp
    FileOperations.cpp
    Menu.cpp
)

target_include_directories(WarehouseManagement PRIVATE .)