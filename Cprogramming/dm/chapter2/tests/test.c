#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../vendor/miniunit.h"
#include "../link_list.h"
#include "2.h"

int tests_run = 0;


static char *test_delete_and_insert_sub()
{
    LinkList la = create_link_list_from_string("abc");
    LinkList lb = create_link_list_from_string("def");
    char *ans;

    DeleteAndInsertSub(&la, &lb, 1, 1, 2);
    ans = link_list_to_string(la);
    mu_assert("delete and insert 1.1", strcmp(ans, "c") == 0);
    free(ans);
    ans = link_list_to_string(lb);
    mu_assert("delete and insert 1.1", strcmp(ans, "abdef") == 0);
    free(ans);

    destory_link_list(la);
    destory_link_list(lb);
    
    la = create_link_list_from_string("abc");
    lb = create_link_list_from_string("def");

    DeleteAndInsertSub(&la, &lb, 2, 1, 2);
    ans = link_list_to_string(la);
    mu_assert("delete and insert 2.1", strcmp(ans, "a") == 0);
    free(ans);
    ans = link_list_to_string(lb);
    mu_assert("delete and insert 2.2", strcmp(ans, "bcdef") == 0);
    free(ans);

    destory_link_list(la);
    destory_link_list(lb);
    
    la = create_link_list_from_string("abc");
    lb = create_link_list_from_string("def");

    DeleteAndInsertSub(&la, &lb, 2, 4, 2);
    ans = link_list_to_string(la);
    mu_assert("delete and insert 3.1", strcmp(ans, "a") == 0);
    free(ans);
    ans = link_list_to_string(lb);
    mu_assert("delete and insert 3.2", strcmp(ans, "defbc") == 0);
    free(ans);

    destory_link_list(la);
    destory_link_list(lb);

    return 0;
}

static char *run()
{
    mu_run_test(test_delete_and_insert_sub);

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
