#include <stdio.h>

void func(int m, int d[], int *n);

int main()
{
    int n, d[20];

    func(20, d, &n);
    printf("%d", n);

    return 0;
}

void func(int m, int d[], int *n)
{
    int i, count;

    for (i = 1, count = 0;i <= m;i++)
        if (m % i == 0)
            d[count++] = i;
    *n = count;
}
