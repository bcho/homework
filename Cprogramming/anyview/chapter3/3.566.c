#include <stdio.h>

int main()
{
    int a = 1234, b = 4567;
    long c;

    // core
    c = a % 1000 * 1000 + b % 1000;

    printf("%ld", c);

    return 0;
}
