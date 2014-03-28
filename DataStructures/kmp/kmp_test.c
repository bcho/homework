#include "../vendor/miniunit.h"

#include "naive.h"
#include "kmp.h"


int tests_run = 0;


static char *test_naive()
{
    mu_assert("non exists", naive_match("abc", "d") == -1);
    mu_assert("needle too long", naive_match("a", "dde") == -1);
    
    mu_assert("match head", naive_match("abc", "a") == 0);
    mu_assert("match tail", naive_match("abc", "c") == 2);
    
    mu_assert("match long", naive_match("abcdefghijklmn", "defghi") == 3);
    mu_assert("match duplicate", naive_match("abcdefdefdef", "def") == 3);
    mu_assert("wiki example", naive_match("ABC ABCDAB ABCDABCDABDE", "ABCDABD") == 15);

    return OK;
}

static char *test_kmp()
{
    mu_assert("non exists", kmp_match("abc", "d") == -1);
    mu_assert("needle too long", kmp_match("a", "dde") == -1);
    
    mu_assert("match head", kmp_match("abc", "a") == 0);
    mu_assert("match tail", kmp_match("abc", "c") == 2);
    
    mu_assert("match long", kmp_match("abcdefghijklmn", "defghi") == 3);
    mu_assert("match duplicate", kmp_match("abcdefdefdef", "def") == 3);
    mu_assert("wiki example", kmp_match("ABC ABCDAB ABCDABCDABDE", "ABCDABD") == 15);

    return OK;
}

static char *run()
{
    mu_run_test(test_naive);
    mu_run_test(test_kmp);

    return OK;
}

TEST_MAIN;
