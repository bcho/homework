#include <stdio.h>

void func(int v[], int n, int k, int c[]);

int main()
{
    int n = 5;
    int v[5] = {1, 1, 1, 2, 2};
    int k = 2;
    int c[2];

    func(v, n, k, c);
    for (n = 0;n < k;n++)
        printf("%d ", c[n]);

    return 0;
}

void func(int v[], int n, int k, int c[])
{
    int i;

    for (i = 0;i < k;i++)
        c[i] = 0;
    for (i = 0;i < n;i++)
        c[v[i] - 1]++;
}
