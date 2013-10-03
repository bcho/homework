cmake_minimum_required(VERSION 2.8)
project(chapter2)

set(CMAKE_C_FLAGS "-Wall -g")

include_directories(.)

add_library(link_list link_list.c)


add_subdirectory(tests)
