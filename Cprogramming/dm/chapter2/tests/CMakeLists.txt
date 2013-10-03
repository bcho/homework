include_directories(../ ../vendor)

add_executable(test_link_list.test test_link_list.c)
target_link_libraries(test_link_list.test link_list)
