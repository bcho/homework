#include <stdio.h>

int main()
{
    int a = 408;

    // core
    a = a / 100 + a % 100 * 10;

    printf("%d", a);

    return 0;
}
