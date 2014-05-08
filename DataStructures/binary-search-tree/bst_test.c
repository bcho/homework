#include "../vendor/miniunit.h"

#include "bst.h"

int tests_run = 0;

static char *test_init()
{
    struct bst *t;

    t = bst_init(0, NULL);
    mu_assert("init empty", t == NULL);
    bst_destory(t);

    t = bst_init(2, "abcde");
    mu_assert("init subset", t != NULL);
    bst_destory(t);

    return OK;
}

static char *test_search()
{
    struct bst *t;
    struct bst *r;

    t = bst_init(6, "abcdef");

    mu_assert("search root", bst_search(t, t->data) == t);

    r = bst_search(t, 'b');
    mu_assert("search b", r != NULL);
    mu_assert("search b", r->data == 'b');
    mu_assert("search b", r != t);

    mu_assert("search non-exists", bst_search(t, 'z') == NULL);

    return OK;
}

static char *test_structure()
{
    struct bst *t;

    t = bst_init(6, "abcdef");
    bst_prefix_print(t);
    bst_destory(t);
    printf("\n");
    
    t = bst_init(32, "packmyboxwithfivedozenliquorjugs");
    bst_prefix_print(t);
    bst_destory(t);
    printf("\n");

    return OK;
}

static char *test_remove()
{
    struct bst *t;

    t = bst_init(26, "abcdefghikjlmnopqrstuvwxzy");
    
    bst_remove(&t, 'a');
    bst_prefix_print(t);
    printf("\n");
    
    bst_remove(&t, 'h');
    bst_prefix_print(t);
    printf("\n");


    bst_destory(t);

    return OK;
}

static char *run()
{
    mu_run_test(test_init);
    mu_run_test(test_search);
    mu_run_test(test_structure);
    mu_run_test(test_remove);

    return OK;
}

TEST_MAIN;
