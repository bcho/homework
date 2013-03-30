#include <stdio.h>

long func(int a[], int n);

int main()
{
    int n = 5;
    int a[5] = {1, 2, 3, 4, 5};

    printf("%ld", func(a, n));

    return 0;
}

long func(int a[], int n)
{
    long ret;
    int i;

    for (ret = 1, i = 0;i < n;i++)
        ret *= a[i];

    return ret;
}
