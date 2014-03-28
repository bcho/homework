include_directories(. ../vendor)

add_executable("kmp_test"
               "naive.c"
               "kmp.c"
               "kmp_test.c")
