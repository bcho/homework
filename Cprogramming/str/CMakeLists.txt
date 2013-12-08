cmake_minimum_required(VERSION 2.8)
project(str)

set(CMAKE_C_FLAGS "-Wall -g")

include_directories(.)

add_library(str str.c)

add_subdirectory(tests)
