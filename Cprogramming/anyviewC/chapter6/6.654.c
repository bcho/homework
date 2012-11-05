#include <stdio.h>

int main()
{
    int n = 3, i, j;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};
    double avg;

    for (i = 0, avg = 0;i < n;i++)
        for (j = 0;j < n;j++)
            avg += a[i][j];
    avg /= n * n;

    printf("%lf", avg);

    return 0;
}
