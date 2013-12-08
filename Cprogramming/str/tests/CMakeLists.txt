include_directories(../ ../vendor)

add_executable(test_str test_str.c)
target_link_libraries(test_str str)
