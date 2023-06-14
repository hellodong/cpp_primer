cmake_minimum_required(VERSION 3.5)

project(screen)

#include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(screen src/main.cpp src/Screen.cpp)
