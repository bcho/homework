#include <stdio.h>

int main()
{
    int a, b, c, d;

    a = b = 20;
    c = 58;
    d = (c - a / 5) / (c - 2 * b);

    printf("(%d-%d/5)/(%d-2*%d)=%d\n", c, a, c, b, d);

    return 0;
}
