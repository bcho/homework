#include <stdio.h>

int main()
{
    int a = 1234, b = 4567;
    long c;

    // core
    c = (a % 10 * 100 + a % 100 / 10 * 10 + a % 1000 / 100) * 1000 +\
        (b % 10 * 100 + b % 100 / 10 * 10 + b % 1000 / 100);

    printf("%ld", c);

    return 0;
}
