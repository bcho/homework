#include <stdio.h>

int func(long n, int d[]);

int main()
{
    int d[20];

    printf("%d", func(3721, d));
    printf("%d %d", d[0], d[1]);

    return 0;
}

int func(long n, int d[])
{
    char s[20];
    int i;

    sprintf(s, "%ld", n);
    for (i = 0;s[i];i++)
        d[i] = s[i] - '0';

    return i;
}
