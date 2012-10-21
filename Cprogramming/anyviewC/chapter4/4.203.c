#include <stdio.h>

int main()
{
    int a = 0, b = -20, c;

    c = a > b ? b * b : 0;

    printf("c=%d\n", c);

    return 0;
}
