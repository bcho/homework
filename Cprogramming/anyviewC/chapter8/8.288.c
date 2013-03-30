#include <stdio.h>

void func(int (*p)[4], int n, float *avg);

int main()
{
    int p[3][4] = {
        {45, 38, -6, 78},
        {34, 48, 70, 4},
        {-9, 0, 4, 20}
    };
    int i;
    float avg[3];

    func(p, 3, avg);

    for (i = 0;i < 3;i++)
        printf("%f ", avg[i]);

    return 0;
}

void func(int (*p)[4], int n, float *avg)
{
    int i, j;

    for (i = 0;i < n;i++)
        avg[i] = 0;
    for (i = 0;i < n;i++)
        for (j = 0;j < 4;j++)
            avg[i] += p[i][j];
    for (i = 0;i < n;i++)
        avg[i] /= 4;
}
