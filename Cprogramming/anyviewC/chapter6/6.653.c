#include <stdio.h>

int main()
{
    int n = 3, i, j, sum;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, sum = 0;i < n;i++)
        for (j = 0;j < n;j++)
            sum += a[i][j];

    printf("%d", sum);

    return 0;
}
