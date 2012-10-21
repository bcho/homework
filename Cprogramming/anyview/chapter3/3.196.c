#include <stdio.h>

int main()
{
    int a, b, c;

    a = 10;
    printf("a=%d ", a);

    b = --a + 5;
    printf("b=%d ", b);

    c = 7 + a--;
    printf("c=%d %d\n", c, a);

    return 0;
}
