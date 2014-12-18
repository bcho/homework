#include "lib/miniunit.h"
#include <string.h>

#include "sys_call.h"
#include "config.h"
#include "errno.h"
#include "fs.h"

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
test_open_without_absolute_path()
{
    struct user u;

    init();

    user_get_by_id(1, &u);

    mu_assert("open: need absolute path",
              open(&u, "not_absolute_path", PERM_RD) == - E_FAIL);

    return 0;
}

char *
test_open_not_exist_file()
{
    struct user u;

    init();

    user_get_by_id(1, &u);

    mu_assert("open: not exist file",
              open(&u, "/not_exist_file", PERM_RD) == - E_INVALID_TYPE);

    return 0;
}

char *
test_open_dir()
{
    struct user u;

    init();

    user_get_by_id(1, &u);

    mu_assert("open: dir", open(&u, "/", PERM_RD) == - E_INVALID_TYPE);

    return 0;
}

char *
test_create()
{
    struct user u;

    init();

    user_get_by_id(1, &u);

    mu_assert("create: dir",
              create(&u, TYPE_DIR, "/foo", PERM_WR | PERM_RD, PERM_RD) == E_OK);
    mu_assert("create: file",
              create(&u, TYPE_FILE, "/foo/bar", PERM_RD, PERM_RD) == E_OK);

    return 0;
}

char *
test_read_write()
{
    int fd;
    struct user u;
    char buf[100];
    char *expected = "hello world";

    init();

    user_get_by_id(1, &u);

    create(&u, TYPE_FILE, "/test", PERM_RD | PERM_WR, PERM_RD);

    fd = open(&u, "/test", PERM_WR);
    mu_assert("write", write(fd, expected) == strlen(expected));
    close(fd);

    fd = open(&u, "/test", PERM_RD);
    mu_assert("read", read(fd, buf) == strlen(expected));
    mu_assert("read", strcmp(buf, expected) == 0);
    close(fd);

    return 0;
}

char *
test_mv()
{
    int fd;
    struct user u;

    init();

    user_get_by_id(1, &u);

    create(&u, TYPE_FILE, "/bar", PERM_RD, PERM_RD);
    create(&u, TYPE_DIR, "/foo", PERM_WR | PERM_RD, PERM_RD);
    mv(&u, "/bar", "/foo");

    mu_assert("mv", open(&u, "/foo/bar", PERM_RD) > 0);

    return 0;
}

char *
test_delete()
{
    struct user u;

    init();

    user_get_by_id(1, &u);
    
    create(&u, TYPE_FILE, "/bar", PERM_RD, PERM_RD);
    delete(&u, "/bar");
    mu_assert("delete", open(&u, "/bar", PERM_RD) == - E_INVALID_TYPE);

    return 0;
}

char *
run()
{
    mu_run_test(test_init);
    mu_run_test(test_useradd_too_many_user);
    mu_run_test(test_user_get_by_id_not_found);
    mu_run_test(test_open_without_absolute_path);
    mu_run_test(test_open_not_exist_file);
    // TODO test open with permission / too many fd
    mu_run_test(test_create);
    mu_run_test(test_read_write);
    mu_run_test(test_mv);
    mu_run_test(test_delete);

    return 0;
}

TEST_MAIN;
