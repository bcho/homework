#include <stdio.h>

int main()
{
    int n = 3, i, smin;
    int a[3][3] = {{-1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, smin = 2 << 29;i < n;i++) {
        smin = (smin < a[0][i]) ? smin : a[0][i];
        smin = (smin < a[n - 1][i]) ? smin : a[n - 1][i];
    }
    for (i = 1;i < n - 1;i++) {
        smin = (smin < a[i][0]) ? smin : a[i][0];
        smin = (smin < a[i][n - 1]) ? smin : a[i][n - 1];
    }

    printf("%d", smin);

    return 0;
}
