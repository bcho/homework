#include <stdio.h>

void func(int (*p)[4], int n, int *sum);

int main()
{
    int p[3][4] = {
        {45, 38, -6, 78},
        {34, 48, 70, 4},
        {-9, 0, 4, 20}
    };
    int i;
    int sum[3];

    func(p, 3, sum);

    for (i = 0;i < 3;i++)
        printf("%d ", sum[i]);

    return 0;
}

void func(int (*p)[4], int n, int *sum)
{
    int i, j;

    for (i = 0;i < n;i++) {
        sum[i] = 0;
        for (j = 0;j < 4;j++)
            sum[i] += p[i][j];
    }
}
