#include <stdio.h>
#include <string.h>
#include "../vendor/miniunit.h"

#include "singly-linked-list.h"

int tests_run = 0;

static char *test_create_list()
{
    struct list_head *head;
   
    head = list_create();
    mu_assert("Create list failed.", head != NULL);
    mu_assert("Newly created list has no items", head->first == NULL);

    return OK;
}

static char *test_create_list_item()
{
    struct list_item *item;

    item = list_item_create((void *) "hello");

    mu_assert("Create list item failed.", item != NULL);
    mu_assert("Newly created list item doesn't have next item",
              item->next == NULL);
    mu_assert("Data should stay the same.",
              strcmp((char *) item->data, "hello") == 0);

    return OK;
}

static char *test_destory_list()
{
    struct list_head *list;

    list = list_create();
    list_destory(&list);

    mu_assert("Destory list failed.", list == NULL);

    // TODO test multiple items list

    return OK;
}

static char *test_destory_list_item()
{
    struct list_item *item;

    item = list_item_create((void *) "test");
    list_item_destory(&item);

    mu_assert("Destory item failed.", item == NULL);

    return OK;
}

static char *test_list_empty()
{
    struct list_head *list;

    list = list_create();

    mu_assert("Newly created list should be empty", list_empty(list) == 1);

    // TODO test multiple items list
    
    return OK;
}

static char *test_list_length()
{
    struct list_head *list;

    list = list_create();

    mu_assert("Newly created list's length should be 0",
              list_length(list) == 0);

    // TODO test multiple items list
    
    return OK;
}

static char *run()
{
    mu_run_test(test_create_list);
    mu_run_test(test_create_list_item);
    mu_run_test(test_destory_list);
    mu_run_test(test_destory_list_item);
    mu_run_test(test_list_empty);
    mu_run_test(test_list_length);

    return OK;
}

TEST_MAIN
