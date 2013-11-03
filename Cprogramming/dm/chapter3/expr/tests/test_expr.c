#include <stdio.h>

#include "../vendor/miniunit.h"
#include "../expr.h"
#include "../lexpr.h"

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

static char *test_logic_validate()
{
    mu_assert("lv1", validate_lexpr("P + Q") == 1);
    mu_assert("lv2", validate_lexpr("P * Q") == 1);
    mu_assert("lv3.1", validate_lexpr("~P") == 1);
    mu_assert("lv3.2", validate_lexpr("P") == 1);
    mu_assert("lv4", validate_lexpr("~(P + Q)") == 1);
    mu_assert("lv5", validate_lexpr("~P + Q") == 1);
    mu_assert("lv6", validate_lexpr("~P * Q") == 1);
    mu_assert("lv7", validate_lexpr("P + ~Q") == 1);
    
    mu_assert("lv8", validate_lexpr("P * + Q") == 0);
    mu_assert("lv9", validate_lexpr("P + * Q") == 0);
    mu_assert("lv10", validate_lexpr("P + Q)") == 0);
    mu_assert("lv11", validate_lexpr("(P + Q") == 0);
    mu_assert("lv12", validate_lexpr("O+(P+Q") == 0);

    mu_assert("lv13", validate_lexpr("P = Q") == 1);
    mu_assert("lv14", validate_lexpr("P = ") == 0);
    mu_assert("lv15", validate_lexpr("P - Q") == 1);
    mu_assert("lv16", validate_lexpr("P - ") == 0);
    mu_assert("lv17", validate_lexpr("- P") == 0);
    mu_assert("lv18", validate_lexpr("= P") == 0);
    mu_assert("lv19", validate_lexpr("P + Q = R") == 1);
    mu_assert("lv19", validate_lexpr("P - Q - R") == 1);
    mu_assert("lv20", validate_lexpr("P = Q - R") == 1);
    mu_assert("lv21", validate_lexpr("P = Q = R") == 1);
    mu_assert("lv22", validate_lexpr("P * Q = R") == 1);
    mu_assert("lv23", validate_lexpr("P * Q - R") == 1);
    mu_assert("lv24", validate_lexpr("(P + Q) * R + (V * T) - (A + B) * C") == 1);

    return 0;
}

static char *run()
{
    mu_run_test(test_validate);
    mu_run_test(test_logic_validate);

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
