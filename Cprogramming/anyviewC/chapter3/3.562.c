#include <stdio.h>

int main()
{
    int a = 123, b = 456, c;

    // core
    c = (a % 10 * 10 + a % 100 / 10) * 100 + (b % 10 * 10 + b % 100 / 10);

    printf("%d", c);

    return 0;
}
