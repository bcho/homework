#include "../vendor/miniunit.h"

#include "brackets.h"


int tests_run = 0;


static char *test_brackets_single_check()
{
    mu_assert("Empty should be OK.", brackets_single_check(""));
    mu_assert("() should be OK.", brackets_single_check("()"));
    mu_assert("Deep brackets should be OK.",
              brackets_single_check("(((((())))))"));
    mu_assert("Should ignore other things.", brackets_single_check("(abc)"));
    mu_assert("Should ignore other brackets.", brackets_single_check("([)"));

    mu_assert("( should not be OK.", brackets_single_check("(") == 0);
    mu_assert(") should not be OK.", brackets_single_check(")") == 0);
    mu_assert("Deep brackets should not be OK.",
              brackets_single_check("(((((())))") == 0);
    mu_assert("Exchange order should not be OK.",
              brackets_single_check(")(") == 0);

    return OK;
}

static char *test_brackets_check()
{
    mu_assert("Empty should be OK.", brackets_check(""));
    mu_assert("() should be OK.", brackets_check("()"));
    mu_assert("([]) should be OK.", brackets_check("([])"));
    mu_assert("([{}]) should be OK.", brackets_check("([{}])"));
    mu_assert("Deep brackets should be OK.",
              brackets_check("(((([{}]))))"));
    mu_assert("Should ignore other things.", brackets_check("(abc)"));

    mu_assert("( should not be OK.", brackets_check("(") == 0);
    mu_assert(") should not be OK.", brackets_check(")") == 0);
    mu_assert("Deep brackets should not be OK.",
              brackets_check("(((((())))") == 0);
    mu_assert("Exchange order should not be OK.",
              brackets_check(")(") == 0);
    mu_assert("Exchange order should not be OK.",
              brackets_check("[)[") == 0);
    mu_assert("Mis-nested should not be OK.",
              brackets_check("[)]") == 0);

    return OK;
}

static char *run()
{
    mu_run_test(test_brackets_single_check);
    mu_run_test(test_brackets_check);

    return OK;
}

TEST_MAIN
