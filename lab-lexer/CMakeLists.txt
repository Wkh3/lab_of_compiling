project(Lexer)

cmake_minimum_required(VERSION 3.4)

include_directories(${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -std=c++17")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(src_list main.cpp)

add_executable(lexer ${src_list})