cmake_minimum_required(VERSION 3.20)

project(x-format)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_TEST ON)

aux_source_directory(src SRC_LIST)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(xformat_static STATIC ${SRC_LIST})
add_library(xformat::static ALIAS xformat_static)
set_target_properties(xformat_static PROPERTIES OUTPUT_NAME "xformat")

add_library(xformat_shared SHARED ${SRC_LIST})
add_library(xformat::shared ALIAS xformat_shared)
set_target_properties(xformat_shared PROPERTIES OUTPUT_NAME "xformat")

if(BUILD_TEST)
    message("build test targets")
    add_executable(test test/test.cpp ${SRC_LIST})
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
endif()

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
