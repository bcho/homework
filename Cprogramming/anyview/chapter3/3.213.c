#include <stdio.h>

int main()
{
    // should use unsigned?
    int a = 9, b = 11, c, d;

    c = a >> 2;
    d = b << 2;

    printf("c=%d d=%d\n", c, d);

    return 0;
}
