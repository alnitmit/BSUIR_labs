cmake_minimum_required(VERSION 3.29)
project(lab8)

set(CMAKE_CXX_STANDARD 20)

# Создаем исполняемый файл
add_executable(lab8 
    src/main.cpp
    src/menu.cpp
)

# Указываем директории для включения заголовочных файлов
target_include_directories(lab8 PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)