#include "lib/miniunit.h"
#include <string.h>

#include "proc.h"

int tests_run;

char *
test_user_create()
{
    struct user *user;

    user = user_create(1, "test");

    mu_assert("user_create: rv", user != NULL);
    mu_assert("user_create: id", user->id == 1);
    mu_assert("user_create: name", strcmp(user->name, "test") == 0);

    user_destory(user);

    return 0;
}

char *
test_user_get_id()
{
    struct user *user;

    user = user_create(1, "test");

    mu_assert("user_create: id", user_get_id(user) == 1);

    user_destory(user);

    return 0;
}

char *
run()
{
    mu_run_test(test_user_create);
    mu_run_test(test_user_get_id);

    return 0;
}

TEST_MAIN;
