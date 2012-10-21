#include <stdio.h>

int main()
{
    int i, n = 100, s;

    for (i = 1, s = 0;i <= n;i++)
        s += i;

    printf("1+2+...+n=%d\n", s);

    return 0;
}
