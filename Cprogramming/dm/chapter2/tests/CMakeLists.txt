include_directories(../ ../vendor)

add_executable(test_link_list.test test_link_list.c)
target_link_libraries(test_link_list.test link_list)

add_executable(test.test test.c)
target_link_libraries(test.test link_list chapter2)
