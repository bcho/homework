#include "lib/miniunit.h"
#include <stdint.h>

#include "malloc.h"
#include "config.h"

int tests_run;


char *
test_basic()
{
    char *a, *b;
    intptr_t pa, pb;

    a = (char *) my_malloc(sizeof(char) * 10);
    pa = (intptr_t) a;
    mu_assert("malloc: test_basic", a != NULL);
    my_free(a);

    b = (char *) my_malloc(sizeof(char) * 5);
    pb = (intptr_t) b;
    mu_assert("malloc: test_basic", b != NULL);
    my_free(b);

    mu_assert("malloc: test_basic", pa == pb);

    return 0;
}

char *
test_out_of_memory()
{
    char *a;

    mu_assert("malloc: test_out_of_memory", my_malloc(MEM_SIZE) == NULL);

    a = my_malloc(MEM_SIZE / 4);
    mu_assert("malloc: test_out_of_memory", a != NULL);
    my_free(a);

    return 0;
}

char *
test_merge_after_free()
{
    char *a, *b, *c;
    intptr_t pa, pb, pc;

    a = (char *) my_malloc(sizeof(char) * 10);
    mu_assert("malloc: test_merge_after_free", a != NULL);
    pa = (intptr_t) a;
    b = (char *) my_malloc(sizeof(char) * 5);
    pb = (intptr_t) b;
    mu_assert("malloc: test_merge_after_free", b != NULL);
    my_free(a);
    my_free(b);

    c = (char *) my_malloc(sizeof(char) * 30);
    mu_assert("malloc: test_merge_after_free", c != NULL);
    pc = (intptr_t) c;
    my_free(c);

    mu_assert("malloc: test_merge_after_free", pa == pc);

    return 0;
}

char *
test_split()
{
    char *a, *b, *c;
    intptr_t pa, pb, pc;

    a = (char *) my_malloc(sizeof(char) * 30);
    pa = (intptr_t) a;
    mu_assert("malloc: test_split", a != NULL);
    my_free(a);

    b = (char *) my_malloc(sizeof(char) * 5);
    pb = (intptr_t) b;
    mu_assert("malloc: test_split", b != NULL);

    c = (char *) my_malloc(sizeof(char) * 5);
    pc = (intptr_t) c;
    mu_assert("malloc: test_split", c != NULL);

    // TODO tests cover
    // printf("%u %u %u\n", pa, pb, pc);

    return 0;
}

char *
run()
{
    mu_run_test(test_basic);
    mu_run_test(test_out_of_memory);
    mu_run_test(test_merge_after_free);
    mu_run_test(test_split);

    return 0;
}

TEST_MAIN
