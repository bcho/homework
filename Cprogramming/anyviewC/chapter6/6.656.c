#include <stdio.h>

int main()
{
    int n = 2, i, d2sum;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, d2sum = 0;i < n;i++)
        d2sum += a[i][i] + a[i][n - i - 1];
    if (n % 2)
        d2sum -= a[n / 2][n / 2];

    printf("%d", d2sum);

    return 0;
}
