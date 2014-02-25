#include <stdio.h>
#include <string.h>
#include "../vendor/miniunit.h"

#include "hello.h"

int tests_run = 0;


/*
 * Test suits names are as follow:
 *
 *  test_`suite_name`
 */
static char *test_hello()
{
    const char *should_be = "Hello, world!";

    mu_assert("hello world test failed.",
              strcmp(should_be, hello("world")) == 0);

    return OK;
}

static char *run()
{
    mu_run_test(test_hello);

    return OK;
}

TEST_MAIN
