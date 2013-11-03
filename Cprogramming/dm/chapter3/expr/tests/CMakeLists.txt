include_directories(../ ../vendor)

add_executable(test_expr test_expr.c)
target_link_libraries(test_expr expr lexpr)
