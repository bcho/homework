#ifndef MINIUNIT_H
#define MINIUNIT_H

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                     if (message) return message; } while (0)

#define OK NULL

extern int tests_run;

#include <stdio.h>

#define TEST_MAIN int main() \
{ \
    char *result = run(); \
    if (result != 0) \
        printf("%s\n", result); \
    else \
        printf("All passed.\n"); \
    printf("Total %d test(s) runned.\n", tests_run); \
    return 0; \
}

#endif
