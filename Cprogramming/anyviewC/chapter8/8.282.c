#include <stdio.h>

int func(int (*p)[4], int n);

int main()
{
    int p[3][4] = {
        {45, 38, -6, 78},
        {34, 48, 70, 4},
        {-9, 0, 4, 20}
    };

    printf("%d", func(p, 3));

    return 0;
}

int func(int (*p)[4], int n)
{
    int max, i;

    for (i = 0, max = -2 << 15;i < 4 * n;i++)
        if (max < *(*p + i))
            max = *(*p + i);

    return max;
}
