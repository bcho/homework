#include "../vendor/miniunit.h"

#include "list.h"

int tests_run = 0;

enum status compare(elem_type a, elem_type b)
{
    if (a == b)
        return LIST_OK;
    return LIST_FAIL;
}

static char *test_list_insert()
{
    struct list *l;
    elem_type c;

    mu_assert("Init list failed.", list_init(&l) == LIST_OK);
    
    mu_assert("Insert list failed.", list_insert(l, 1, 'a') == LIST_OK);
    mu_assert("Insert list length failed.", list_length(l) == 1);
    mu_assert("Get list item failed.", list_get(l, 1, &c) == LIST_OK);
    mu_assert("Insert list new element failed.", c == 'a');

    mu_assert("Insert list failed.", list_insert(l, 1, 'a') == LIST_OK);
    mu_assert("Insert list failed.", list_insert(l, 1, 'a') == LIST_OK);
    mu_assert("Insert list failed.", list_insert(l, 1, 'a') == LIST_OK);
    mu_assert("Insert list failed.", list_insert(l, 1, 'a') == LIST_OK);
    mu_assert("Insert list failed.", list_insert(l, 1, 'b') == LIST_OK);
    mu_assert("Insert list length failed.", list_length(l) == 6);
    mu_assert("Get list item failed.", list_get(l, 1, &c) == LIST_OK);
    mu_assert("Insert list new element failed.", c == 'b');
    mu_assert("Get list item failed.", list_get(l, 5, &c) == LIST_OK);
    mu_assert("Insert list new element failed.", c == 'a');

    return OK;
}

static char *test_list_delete()
{
    struct list *l;
    elem_type c;

    mu_assert("Init list failed.", list_init(&l) == LIST_OK);
    
    mu_assert("Insert list failed.", list_insert(l, 1, 'a') == LIST_OK);
    mu_assert("Insert list length failed.", list_length(l) == 1);
    mu_assert("Get list item failed.", list_get(l, 1, &c) == LIST_OK);
    mu_assert("Insert list new element failed.", c == 'a');

    mu_assert("Insert list failed.", list_insert(l, 1, 'b') == LIST_OK);
    mu_assert("Insert list failed.", list_insert(l, 1, 'c') == LIST_OK);
    mu_assert("Insert list failed.", list_insert(l, 1, 'd') == LIST_OK);
    mu_assert("Insert list failed.", list_insert(l, 1, 'e') == LIST_OK);
    mu_assert("Insert list failed.", list_insert(l, 1, 'f') == LIST_OK);
    mu_assert("Insert list length failed.", list_length(l) == 6);
    mu_assert("Get list item failed.", list_get(l, 1, &c) == LIST_OK);
    mu_assert("Insert list new element failed.", c == 'f');
    mu_assert("Get list item failed.", list_get(l, 5, &c) == LIST_OK);
    mu_assert("Insert list new element failed.", c == 'b');

    mu_assert("Delete element failed.", list_delete(l, 1, &c) == LIST_OK);
    mu_assert("Delete element mismatch.", c == 'f');
    mu_assert("Get list item failed.", list_get(l, 2, &c) == LIST_OK);
    mu_assert("Insert list new element failed.", c == 'd');

    return OK;
}

static char *test_list_locate()
{
    struct list *l;
    elem_type c;

    mu_assert("Init list failed.", list_init(&l) == LIST_OK);
    
    mu_assert("Insert list failed.", list_insert(l, 1, 'a') == LIST_OK);
    mu_assert("Insert list length failed.", list_length(l) == 1);
    mu_assert("Get list item failed.", list_get(l, 1, &c) == LIST_OK);
    mu_assert("Insert list new element failed.", c == 'a');

    mu_assert("Insert list failed.", list_insert(l, 1, 'b') == LIST_OK);
    mu_assert("Insert list failed.", list_insert(l, 1, 'c') == LIST_OK);
    mu_assert("Insert list failed.", list_insert(l, 1, 'd') == LIST_OK);
    mu_assert("Insert list failed.", list_insert(l, 1, 'e') == LIST_OK);
    mu_assert("Insert list failed.", list_insert(l, 1, 'f') == LIST_OK);
    mu_assert("Insert list failed.", list_insert(l, 1, 'b') == LIST_OK);

    mu_assert("Locate element failed.", list_locate(l, (elem_type) 'c', compare) == 5);
    mu_assert("Locate element failed.", list_locate(l, (elem_type) 'f', compare) == 2);
    mu_assert("Locate element failed.", list_locate(l, (elem_type) 'b', compare) == 1);
    mu_assert("Locate element failed.", list_locate(l, (elem_type) 'a', compare) == 7);

    return OK;
}

static char *run()
{
    mu_run_test(test_list_insert);
    mu_run_test(test_list_delete);
    mu_run_test(test_list_locate);

    return OK;
}

TEST_MAIN
