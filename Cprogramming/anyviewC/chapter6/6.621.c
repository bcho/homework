#include <stdio.h>

int main()
{
    int n = 3, i = 2, imin, j;
    int a[3][3] = {{1, 2, 3}, {1, -2, 3}, {1, 2, 3}};

    for (j = 0, imin = 2 << 29;j < n;j++) {
        imin = (imin < a[i - 1][j]) ? imin : a[i - 1][j];
    }

    printf("%d", imin);

    return 0;
}
