cmake_minimum_required(VERSION 3.10)
project(WarehouseManagementSystem)

# Указываем компилятор C++ и стандарт
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем, что исходные файлы находятся в той же директории, что и CMakeLists.txt
set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Product.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FileOperations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Menu.cpp
)

# Создаем исполняемый файл
add_executable(WarehouseManagement ${SOURCE_FILES})

# Включаем текущую директорию для поиска заголовочных файлов
target_include_directories(WarehouseManagement PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})