#include <stdlib.h>
#include <stdio.h>

#include "../vendor/miniunit.h"
#include "../link_list.h"

int tests_run = 0;

static char *test_create_link_list()
{
    char *str = "hello world";
    LinkList l = create_link_list_from_string(str);

    mu_assert("head", l->data == 'h');
    mu_assert("head+5", get_nth_from_link_list(l, 5)->data == ' ');
    mu_assert("head+6", get_nth_from_link_list(l, 6)->data == 'w');
    mu_assert("head+11", get_nth_from_link_list(l, 10)->next == NULL);

    destory_link_list(l);
}

static char *test_create_link_list_with_dummy()
{
    char *str = "hello world";
    LinkList l = create_link_list_from_string_with_dummy(str);

    mu_assert("head", get_nth_from_link_list(l, 1)->data == 'h');
    mu_assert("head+5", get_nth_from_link_list(l, 6)->data == ' ');
    mu_assert("head+6", get_nth_from_link_list(l, 7)->data == 'w');
    mu_assert("head+11", get_nth_from_link_list(l, 11)->next == NULL);

    destory_link_list(l);
}

static char *run()
{
    mu_run_test(test_create_link_list);
    mu_run_test(test_create_link_list_with_dummy);

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
}
