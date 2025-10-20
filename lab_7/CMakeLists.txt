cmake_minimum_required(VERSION 3.10)
project(InventoryManagement CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
endif()

find_package(PkgConfig)

set(SOURCES
    src/main.cpp
    src/inventory.cpp
)

set(HEADERS
    include/item.h
)

add_executable(inventory_manager ${SOURCES} ${HEADERS})

set_target_properties(inventory_manager PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

install(TARGETS inventory_manager
    RUNTIME DESTINATION bin
    COMPONENT applications
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_TESTING)
    enable_testing()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(inventory_manager PRIVATE -O2)
endif()

message(STATUS "Inventory Management System configured successfully")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")