#include <stdio.h>

int main()
{
    int a = 700, b = -30, c, d;

    c = !a;
    d = !b;

    printf("!%d=%d\n", a, c);
    printf("!%d=%d\n", b, d);

    return 0;
}
