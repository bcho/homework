#include <stdio.h>

int func(int n, int a[]);

int main()
{
    int n, i;
    int a[20];

    scanf("%d", &n);
    printf("%d\n", (n = func(n, a)));
    for (i = 0;i < n;i++)
        printf("%d ", a[i]);

    return 0;
}

int func(int n, int a[])
{
    int i, count;

    for (i = 7, count = 0;i <= n;i++)
        if (i % 7 == 0 || i % 11 == 0)
            a[count++] = i;

    return count;
}
