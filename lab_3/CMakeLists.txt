cmake_minimum_required(VERSION 3.10)
project(LibrarySystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/Article.cpp
    src/LibraryCard.cpp
    src/IndependentPublishingCard.cpp
    src/CollectionOfArticlesCard.cpp
    src/BookCard.cpp
    src/ArticleCard.cpp        
    src/Catalog.cpp
    src/ThematicCatalog.cpp
    src/AlphabeticalCatalog.cpp
)

add_executable(LibrarySystem ${SOURCES})

target_include_directories(LibrarySystem PRIVATE include)

if(MSVC)
    target_compile_options(LibrarySystem PRIVATE /W4)
else()
    target_compile_options(LibrarySystem PRIVATE -Wall -Wextra -pedantic)
endif()