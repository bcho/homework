#include <stdio.h>

int main()
{
    int n = 3, i = 1, j; 
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};
    double iavg;

    for (j = 0, iavg = 0;j < n;j++)
        iavg += a[i][j];
    iavg /= n;

    printf("%lf", iavg);

    return 0;
}
