#include <stdio.h>
#include <assert.h>
#include <setjmp.h>

int test_handled = 0;
jmp_buf test_failed;

void test();

int main()
{
    test_handled = 1;

    if (setjmp(test_failed)) {
        fprintf(stderr, "failed.");
        return 1;
    }
    test();

    return 0;
}

void test()
{
    if (test_handled)
        longjmp(test_failed, 1);
    assert(0);
}
