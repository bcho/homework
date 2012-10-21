#include <stdio.h>

int main()
{
    int a = 100, b, c;

    b = --a - 10;
    printf("b=%d ", b);

    c = 10 + a--;
    printf("c=%d %d\n", c, a);

    return 0;
}
