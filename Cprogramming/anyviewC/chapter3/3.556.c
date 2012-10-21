#include <stdio.h>

int main()
{
    int a = 123, b;

    // core
    b = a / 100 * 100 + a % 10 * 10 + a % 100 / 10;

    printf("%d", b);

    return 0;
}
