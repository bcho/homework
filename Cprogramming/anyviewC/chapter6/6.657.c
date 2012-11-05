#include <stdio.h>

int main()
{
    int n = 3, i;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};
    double d2avg;

    for (i = 0, d2avg = 0;i < n;i++)
        d2avg += a[i][i] + a[i][n - i - 1];
    if (n % 2) {
        d2avg -= a[n / 2][n / 2];
        d2avg /= 2 * n - 1;
    } else {
        d2avg /= 2 * n;
    }

    printf("%lf", d2avg);

    return 0;
}
