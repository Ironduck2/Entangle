cmake_minimum_required(VERSION 3.15)

project(Entangle)

include_directories(include)
add_executable(Entangle src/main.cpp)

target_include_directories(Entangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/External)