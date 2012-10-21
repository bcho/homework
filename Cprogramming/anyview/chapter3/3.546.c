#include <stdio.h>

int main()
{
    int a = 123, b;

    // core
    b = a / 100 * 100 + a % 10;

    printf("%d\n", b);

    return 0;
}
