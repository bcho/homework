#include <stdio.h>

#include "../vendor/miniunit.h"
#include "../expr.h"

int tests_run = 0;

static char *test_validate()
{
    mu_assert("v1", validate_expr("P + Q") == 1);
    mu_assert("v2", validate_expr("P * Q") == 1);
    mu_assert("v3.1", validate_expr("~P") == 1);
    mu_assert("v3.2", validate_expr("P") == 1);
    mu_assert("v4", validate_expr("~(P + Q)") == 1);
    mu_assert("v5", validate_expr("~P + Q") == 1);
    mu_assert("v6", validate_expr("~P * Q") == 1);
    mu_assert("v7", validate_expr("P + ~Q") == 1);
    
    mu_assert("v8", validate_expr("P * + Q") == 0);
    mu_assert("v9", validate_expr("P + * Q") == 0);
    mu_assert("v10", validate_expr("P + Q)") == 0);
    mu_assert("v11", validate_expr("(P + Q") == 0);
    mu_assert("v12", validate_expr("O+(P+Q") == 0);

    return 0;
}

static char *run()
{
    mu_run_test(test_validate);

    return 0;
}

int main()
{
    char *result = run();

    if (result != 0)
        printf(result);
    else
        printf("all passed");
    printf("\ntotal: %d\n", tests_run);

    return 0;
}
