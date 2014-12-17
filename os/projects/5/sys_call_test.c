#include "lib/miniunit.h"

#include "sys_call.h"
#include "config.h"
#include "errno.h"

int tests_run;

char *
test_init()
{
    struct user root;

    init();

    mu_assert("init: root user", user_get_by_id(1, &root) == E_OK);

    return 0;
}

char *
test_useradd_too_many_user()
{
    int i;

    init();

    for (i = 0; i < MAX_USER; i++)
        useradd("test");

    mu_assert("useradd: add too many user",
              useradd("test") == - E_TOO_MANY_USERS);

    return 0;
}

char *
test_user_get_by_id_not_found()
{
    struct user u;

    init();

    mu_assert("user_get_by_id: not found",
              user_get_by_id(0, &u) == - E_FAIL);

    return 0;
}

char *
run()
{
    mu_run_test(test_init);
    mu_run_test(test_useradd_too_many_user);
    mu_run_test(test_user_get_by_id_not_found);

    return 0;
}

TEST_MAIN;
