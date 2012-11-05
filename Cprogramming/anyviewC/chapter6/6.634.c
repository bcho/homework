#include <stdio.h>

int main()
{
    int n = 3, max, i, j;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, max = -2 << 29;i < n;i++)
        for (j = 0;j < n;j++)
            max = (max > a[i][j]) ? max : a[i][j];

    printf("%d", max);

    return 0;
}
