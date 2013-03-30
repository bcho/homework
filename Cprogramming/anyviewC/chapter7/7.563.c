#include <stdio.h>

int func(long n, int d[]);

int main()
{
    int d[20];

    printf("%d", func(3721, d));

    return 0;
}

int func(long n, int d[])
{
    int i;

    for (i = 0;n > 0;n /= 10)
        d[i++] = n % 10;

    return i;
}
