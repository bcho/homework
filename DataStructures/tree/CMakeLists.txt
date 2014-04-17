cmake_minimum_required(VERSION 2.8)
project(tree)

set(CMAKE_C_FLAGS "-Wall -g -lm -std=c89")

add_executable("linked_tree"
               "linked_tree.c")

add_executable("list_tree"
               "list_tree.c")
