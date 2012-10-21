#include <stdio.h>

int main()
{
    int a = 123, b = 456, c;

    // core
    c = b % 10 * 10 + a % 10;

    printf("%d", c);

    return 0;
}
