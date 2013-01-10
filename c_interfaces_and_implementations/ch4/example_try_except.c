#include <stdio.h>
#include "except.h"

void test();
except_t test_error;
except_t uncaught_error;

int main()
{
    test_error.reason = "failed.";
    uncaught_error.reason = "err?";

TRY
    test();
EXCEPT(test_error)
    fprintf(stderr, "test error raised.");
END_TRY;

    return 0;
}

void test() {
    // RAISE(test_error);
    RAISE(uncaught_error);
}
