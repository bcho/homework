#include <stdio.h>
#include <string.h>

#include "../vendor/miniunit.h"
#include "../str.h"

int tests_run = 0;

static char *test_trim()
{
    const char *should_be = "hello";

    mu_assert("no space", strcmp(trim(should_be), should_be) == 0);
    mu_assert("left space", strcmp(trim("     hello"), should_be) == 0);
    mu_assert("left whites", strcmp(trim("\t \t  hello"), should_be) == 0);
    mu_assert("right space", strcmp(trim("hello    "), should_be) == 0);
    mu_assert("right whites", strcmp(trim("hello\t\t\t  "), should_be) == 0);
    mu_assert("both", strcmp(trim("   \thello \t\t"), should_be) == 0);

    return 0;
}

static char *test_join()
{
    const char *strs[3] = {
        "hello",
        "world",
        "dada"
    };
    
    mu_assert("dash", strcmp(join(strs, 3, "-"), "hello-world-dada") == 0);
    mu_assert("space", strcmp(join(strs, 3, " "), "hello world dada") == 0);
    mu_assert("no delim", strcmp(join(strs, 3, ""), "helloworlddada") == 0);
    mu_assert("just one delim", strcmp(join(strs, 1, "-"), "hello") == 0);
    mu_assert("no parts", strcmp(join(strs, 0, "empty"), "") == 0);
    mu_assert("long delim",
              strcmp(join(strs, 3, "<3"), "hello<3world<3dada") == 0);

    const char *e1[2] = {
        "",
        "world"
    };
    mu_assert("first empty parts join",
              strcmp(join(e1, 2, "hello "), "hello world") == 0);
    const char *e2[2] = {
        "hello",
        ""
    };
    mu_assert("last empty parts join",
              strcmp(join(e2, 2, " world"), "hello world") == 0);

    return 0;
}

static char *test_split()
{
    const char *should_be = "hello world dada";
    char *delim = " ";
    const char **ret;
    int count;

    ret = (const char **) split(should_be, " ", &count);
    mu_assert("space", strcmp(should_be, join(ret, count, delim)) == 0);

    ret = (const char **) split(should_be, "abc", &count);
    mu_assert("non-exists delim",
              strcmp(should_be, join(ret, count, delim)) == 0);
    mu_assert("non-exists delim", count == 1);

    ret = (const char **) split("hello<3world<3dada", "<3", &count);
    mu_assert("long delim", strcmp(should_be, join(ret, count, delim)) == 0);

    ret = (const char **) split("", " ", &count);
    mu_assert("empty string", count == 1);
    mu_assert("empty string", strcmp(ret[0], "") == 0);

    ret = (const char **) split("a", "a", &count);
    mu_assert("same as delim", count == 2);
    mu_assert("same as delim",
              strcmp(ret[0], "") == 0 && strcmp(ret[1], "") == 0);

    ret = (const char **) split("abc", "a", &count);
    mu_assert("head split", count == 2);
    mu_assert("head split",
              strcmp(ret[0], "") == 0 && strcmp(ret[1], "bc") == 0);
    
    ret = (const char **) split("abc", "c", &count);
    mu_assert("tail split", count == 2);
    mu_assert("tail split",
              strcmp(ret[0], "ab") == 0 && strcmp(ret[1], "") == 0);

    return 0;
}

static char *run()
{
    mu_run_test(test_trim);
    mu_run_test(test_join);
    mu_run_test(test_split);

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
