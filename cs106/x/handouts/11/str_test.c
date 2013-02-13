#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "str.h"

void test_length_at(char *s);
void test_cmp();

int main()
{
    char *s = "hello world";
    char *cpy;

    test_length_at(s);
    cpy = str_copy(s);
    assert(str_cmp(cpy, s) == 0);
    test_length_at(cpy);
    str_free(cpy);

    test_cmp();

    cpy = str_concat("hello", "world");
    assert(str_cmp(cpy, "helloworld") == 0);
    str_free(cpy);

    cpy = str_copy(s);
    str_append(&cpy, "!");
    assert(str_cmp(cpy, "hello world!") == 0);

    assert(str_find_char("hello", 'o') == 4);
    assert(str_find_char("hello", '!') == -1);
    assert(str_find_str("hello world", "world") == 6);
    assert(str_find_str("hello world", "olleh") == -1);

    cpy = str_substr("hello world", 2, 4);
    assert(str_cmp(cpy, "llo ") == 0);
    str_free(cpy);

    cpy = str_copy(s);
    str_insert(&cpy, 2, "bar");
    assert(str_cmp(cpy, "hebarllo world") == 0);

    cpy = str_copy(s);
    str_replace(&cpy, 2, 3, "bar");
    assert(str_cmp(cpy, "hebar world") == 0);

    cpy = str_copy(s);
    str_append(&cpy, " ");
    str_trim(&cpy);
    assert(str_cmp(cpy, "hello world") == 0);

    printf("all test passed\n");

    return 0;
}

void test_length_at(char *s)
{
    assert(str_length(s) == strlen(s));
    assert(str_at(s, 2) == s[2]);
    assert(str_at(s, -2) == s[-2 + str_length(s)]);
}

void test_cmp()
{
    assert(str_cmp("A", "B") == -1);
    assert(str_cmp("App", "Apple") == -1);
    assert(str_cmp("help", "hello") == 1);
    assert(str_cmp("Apple", "apple") == -1);
    assert(str_cmp("foobar", "foobar") == 0);
}
