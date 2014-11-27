#include "lib/miniunit.h"
#include <string.h>

#include "utils.h"
#include "config.h"

int tests_run;

char *
test_u_sbrk()
{
    char *buf;

    buf = u_sbrk(1);
    mu_assert("u_sbrk: small chunk", buf != (void *) -1);
    *buf = 'c';
    mu_assert("u_sbrk: small chunk", buf[0] == 'c');

    buf = u_sbrk(10);
    mu_assert("u_sbrk: large chunk", buf != (void *) -1);
    memset(buf, 0, 10);
    strncpy(buf, "abc", 3);
    mu_assert("u_sbrk: large chunk", strncmp(buf, "abc", 3) == 0);

    mu_assert("u_sbrk: overflow", u_sbrk(MEM_SIZE + 1) == (void *) -1);
    mu_assert("u_sbrk: underflow", u_sbrk(-MEM_SIZE) == (void *) -1);

    return 0;
}

char *
run()
{
    mu_run_test(test_u_sbrk);

    return 0;
}

TEST_MAIN
