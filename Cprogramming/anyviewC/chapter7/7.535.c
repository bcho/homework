#include <stdio.h>

int func(int v[], int n, int k, int c[]);

int main()
{
    int n = 5;
    int v[5] = {1, 1, 1, 2, 2};
    int k = 2;
    int c[2];

    printf("%d\n", func(v, n, k, c));
    for (n = 0;n < k;n++)
        printf("%d ", c[n]);

    return 0;
}

int func(int v[], int n, int k, int c[])
{
    int i, max;

    for (i = 0;i < k;i++)
        c[i] = 0;
    for (i = 0, max = 0;i < n;i++) {
        c[v[i] - 1]++;
        if (c[v[i] - 1] > c[max])
            max = v[i] - 1;
    }

    return max + 1;
}
