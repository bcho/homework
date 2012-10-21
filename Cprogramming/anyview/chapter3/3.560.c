#include <stdio.h>

int main()
{
    int a = 100, b = 357, c;

    // core
    c = a % 10 * 10 + b % 10;

    printf("%d", c);

    return 0;
}
