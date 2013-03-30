#include <stdio.h>

long func(int a[], int n);

int main()
{
    int n = 5;
    int a[5] = {1, 2, 3, 4, 5};

    printf("%ld", func(a, n));

    return 0;
}

#define SQR(a) (a) * (a)

long func(int a[], int n)
{
    long ret;
    int i;

    for (ret = 0, i = 0;i < n;i++)
        ret += SQR(a[i]);

    return ret;
}
