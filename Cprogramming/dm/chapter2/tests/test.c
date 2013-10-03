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

static char *test_insert()
{
    LinkList l;
    char *ans;

    l = create_link_list_from_string("abc");

    Insert(&l, 1, 'd');
    ans = link_list_to_string(l);
    mu_assert("insert 1", strcmp(ans, "adbc") == 0);

    free(ans);
    destory_link_list(l);
    
    l = create_link_list_from_string("abc");

    Insert(&l, 3, 'd');
    ans = link_list_to_string(l);
    mu_assert("insert 2", strcmp(ans, "abcd") == 0);

    free(ans);
    destory_link_list(l);
    
    l = create_link_list_from_string("abc");

    Insert(&l, 0, 'd');
    ans = link_list_to_string(l);
    mu_assert("insert 3", strcmp(ans, "dabc") == 0);

    free(ans);
    destory_link_list(l);

    return 0;
}

static char *test_purge()
{
    LinkList l;
    char *ans;

    l = create_link_list_from_string("abc");
    Purge(&l);
    ans = link_list_to_string(l);
    mu_assert("purege 1", strcmp(ans, "abc") == 0);

    free(ans);
    destory_link_list(l);
    
    l = create_link_list_from_string("aaabbbcccc");
    Purge(&l);
    ans = link_list_to_string(l);
    mu_assert("purege 2", strcmp(ans, "abc") == 0);

    free(ans);
    destory_link_list(l);
    
    l = create_link_list_from_string("abcabc");
    Purge(&l);
    ans = link_list_to_string(l);
    mu_assert("purege 3", strcmp(ans, "abc") == 0);

    free(ans);
    destory_link_list(l);

    return 0;
}

static char *test_inverse()
{
    LinkList l;
    char *ans;
    
    l = create_link_list_from_string_with_dummy("a");
    Inverse(&l);
    ans = link_list_to_string(l);
    mu_assert("inverse 1", strcmp(ans, "a") == 0);

    free(ans);
    destory_link_list(l);

    l = create_link_list_from_string_with_dummy("abc");
    Inverse(&l);
    ans = link_list_to_string(l);
    mu_assert("inverse 2", strcmp(ans, "cba") == 0);

    free(ans);
    destory_link_list(l);


    return 0;
}

static char *test_merge()
{
    LinkList la, lb, lc;
    char *ans;

    la = create_link_list_from_string_with_dummy("abc");
    lb = create_link_list_from_string_with_dummy("def");
    lc = create_link_list_from_string_with_dummy(""); // carry dummy
    Merge(la, lb, &lc);
    ans = link_list_to_string(la);
    mu_assert("merge 1a", strcmp(ans, "") == 0);
    free(ans);
    ans = link_list_to_string(lb);
    mu_assert("merge 1b", strcmp(ans, "") == 0);
    free(ans);
    ans = link_list_to_string(lc);
    mu_assert("merge 1c", strcmp(ans, "adbecf") == 0);
    free(ans);

    destory_link_list(la);
    destory_link_list(lb);
    destory_link_list(lc);

    la = create_link_list_from_string_with_dummy("");
    lb = create_link_list_from_string_with_dummy("def");
    lc = create_link_list_from_string_with_dummy(""); // carry dummy
    Merge(la, lb, &lc);
    ans = link_list_to_string(la);
    mu_assert("merge 2a", strcmp(ans, "") == 0);
    free(ans);
    ans = link_list_to_string(lb);
    mu_assert("merge 2b", strcmp(ans, "") == 0);
    free(ans);
    ans = link_list_to_string(lc);
    mu_assert("merge 2c", strcmp(ans, "def") == 0);
    free(ans);

    destory_link_list(la);
    destory_link_list(lb);
    destory_link_list(lc);
    
    la = create_link_list_from_string_with_dummy("abc");
    lb = create_link_list_from_string_with_dummy("defgh");
    lc = create_link_list_from_string_with_dummy(""); // carry dummy
    Merge(la, lb, &lc);
    ans = link_list_to_string(la);
    mu_assert("merge 2a", strcmp(ans, "") == 0);
    free(ans);
    ans = link_list_to_string(lb);
    mu_assert("merge 2b", strcmp(ans, "") == 0);
    free(ans);
    ans = link_list_to_string(lc);
    mu_assert("merge 2c", strcmp(ans, "adbecfgh") == 0);
    free(ans);

    destory_link_list(la);
    destory_link_list(lb);
    destory_link_list(lc);

    return 0;
}

static char *run()
{
    mu_run_test(test_delete_and_insert_sub);
    mu_run_test(test_insert);
    mu_run_test(test_purge);
    mu_run_test(test_inverse);
    mu_run_test(test_merge);

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
