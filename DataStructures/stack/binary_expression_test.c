#include "../vendor/miniunit.h"

#include "binary_expression.h"


int tests_run = 0;


static char *test_calculate()
{
    mu_assert("1", calculate("1") == 1);

    mu_assert("1 + 1", calculate("1 + 1") == 2);
    mu_assert("1 +1", calculate("1 +1") == 2);
    mu_assert("1+ 1", calculate("1+ 1") == 2);
    mu_assert("1+1", calculate("1+1") == 2);

    mu_assert("2 * 3 + 4 / 5", calculate("2 * 3 + 4 / 5") == 6);
    mu_assert("2 * 3 + 5 / 4", calculate("2 * 3 + 5 / 4") == 7);
    mu_assert("2 - 3 * 4 / 2", calculate("2 - 3 * 4 / 2") == -4);
    //mu_assert("-2 - 3 * 4 / 2", calculate("-2 - 3 * 4 / 2") == -8);
    
    mu_assert("2 * (3 + 9)", calculate("2 * (3 + 9)") == 24);

    mu_assert("2 * (3 + 9) / 6", calculate("2 * (3 + 9) / 6") == 4);
    mu_assert("2 * ((3 + 9) - 6)", calculate("2 * ((3 + 9) - 6)") == 12);
    
    mu_assert("200 * 1000", calculate("200 * 1000") == 200 * 1000);

    return OK;
}

static char *run()
{
    mu_run_test(test_calculate);

    return OK;
}

TEST_MAIN;
