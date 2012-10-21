#include <stdio.h>

int main()
{
    int a, b, c, d, e, f, g;

    a = 215;
    b = 19;
    c = 75;
    d = a / b;
    e = a % b;
    f = a / c;
    g = a % c;

    printf("%d/%d=%d...%d\n", a, b, d, e);
    printf("%d/%d=%d...%d\n", a, c, f, g);

    return 0;
}
