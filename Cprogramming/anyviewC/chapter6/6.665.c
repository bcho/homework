#include <stdio.h>

int main()
{
    int n = 2, i, smax;
    int a[3][3] = {{-1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, smax = -2 << 29;i < n;i++) {
        smax = (smax > a[0][i]) ? smax : a[0][i];
        smax = (smax > a[n - 1][i]) ? smax : a[n - 1][i];
    }
    for (i = 1;i < n - 1;i++) {
        smax = (smax > a[i][0]) ? smax : a[i][0];
        smax = (smax > a[i][n - 1]) ? smax : a[i][n - 1];
    }

    printf("%d", smax);

    return 0;
}
