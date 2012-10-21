#include <stdio.h>

int main()
{
    int a = 360;

    // core
    a = a % 10 * 100 + a / 10;

    printf("%d", a);

    return 0;
}
