#include <stdio.h>

int main()
{
    int a, b, c, d, e;

    a = 17;
    b = 5;
    c = a * b;
    d = a / b;
    e = a % b;

    printf("%d*%d=%d\n", a, b, c);
    printf("%d/%d=%d\n", a, b, d);
    printf("%d%%%d=%d\n", a, b, e);

    return 0;
}
