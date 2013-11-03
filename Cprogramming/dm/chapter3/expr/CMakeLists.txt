cmake_minimum_required(VERSION 2.8)
project(expr)

set(CMAKE_C_FLAGS "-Wall -g")

include_directories(.)

add_library(expr expr.c)
add_library(lexpr lexpr.c)

add_subdirectory(tests)
