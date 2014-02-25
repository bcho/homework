# Also include `miniunit.h`.
include_directories(. ../vendor)

add_library(hello hello.c)

# Test suit executable's name is as follow:
#
#       `subpart_name`_test
add_executable(hello_test hello_test.c)

target_link_libraries(hello_test hello)
