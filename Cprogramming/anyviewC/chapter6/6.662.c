#include <stdio.h>

int main()
{
    int n = 3, i, ss;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, ss = 0;i < n;i++)
        ss += (n - 1) ? a[0][i] + a[n - 1][i] : a[0][i];
    for (i = 1;i < n - 1;i++)
        ss += (n - 1) ? a[i][0] + a[i][n - 1] : a[i][0];

    printf("%d", ss);

    return 0;
}
