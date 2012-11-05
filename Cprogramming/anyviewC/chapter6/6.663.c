#include <stdio.h>

int main()
{
    int n = 3, i;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};
    double savg;

    for (i = 0, savg = 0;i < n;i++)
        savg += (n - 1) ? a[0][i] + a[n - 1][i] : a[0][i];
    for (i = 1;i < n - 1;i++)
        savg += (n - 1) ? a[i][0] + a[i][n - 1] : a[i][0];
    if (n > 1)
        savg /= n * n - (n - 2) * (n - 2);

    printf("%lf", savg);

    return 0;
}
