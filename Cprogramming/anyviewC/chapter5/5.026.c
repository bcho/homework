#include <stdio.h>

int main()
{
    int i, n = 100, s;

    for (i = 1, s = 0;i <= n;i++)
        if (i % 2)
            s += i;

    printf("%d", s);

    return 0;
}
