#include <stdio.h>

int main()
{
    int a[15][15] = {{1, 2, 3}, {4, 5, 6}}, b[15][15];
    int m = 2, n = 3, i, j;

    for (i = 0;i < m;i++)
        for (j = 0;j < n;j++)
            b[j][i] = a[i][j];

    for (i = 0;i < n;i++) {
        for (j = 0;j < m;j++)
            printf("%d ", b[i][j]);
        printf("\n");
    }

    return 0;
}
