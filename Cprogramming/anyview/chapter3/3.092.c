#include <stdio.h>

int main()
{
    int a, b, c;
    a = 11;
    b = 2;
    c = a / b * (b - a % 10);

    printf("%d", c);

    return 0;
}
