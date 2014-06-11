cmake_minimum_required(VERSION 2.8)
project(relationships)

set(CMAKE_C_FLAGS "-Wall -g -lm")

include_directories(. ../vendor)

add_executable("relationships"
               "relationships.c")
