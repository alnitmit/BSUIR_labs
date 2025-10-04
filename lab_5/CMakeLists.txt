cmake_minimum_required(VERSION 3.10)
project(ExpressionTreeCalculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем правильные пути к исходным файлам
add_executable(ExpressionTreeCalculator
    src/main.cpp
    src/ExpressionTree.cpp
)

# Включаем директории с заголовочными файлами
target_include_directories(ExpressionTreeCalculator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Устанавливаем свойства для более строгих предупреждений
if(MSVC)
    target_compile_options(ExpressionTreeCalculator PRIVATE /W4)
else()
    target_compile_options(ExpressionTreeCalculator PRIVATE -Wall -Wextra -pedantic)
endif()