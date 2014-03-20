include_directories(. ../vendor)

add_executable("brackets_test"
               "brackets.c"
               "stack.c"
               "brackets_test.c")

add_executable("binary_expression_test"
               "binary_expression.c"
               "binary_expression_test.c")
