#include <stdio.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

int func(int n, int c, int d, int a[]);

int main()
{
    int n, c, d, i;
    int a[20];

    scanf("%d %d %d", &n, &c, &d);
    printf("%d\n", n = func(n, c, d, a));
    for (i = 0;i < n;i++)
        printf("%d ", a[i]);

    return 0;
}

int func(int n, int c, int d, int a[])
{
    int i, count;

    for (i = max(c, d), count = 0;i <= n;i++)
        if (i % c == 0 && i % d == 0)
            a[count++] = i;

    return count;
}
