#include <stdio.h>

int main()
{
    int n = 3, min, i, j;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, min = 2 << 29;i < n;i++)
        for (j = 0;j < n;j++)
            min = (min < a[i][j]) ? min : a[i][j];

    printf("%d", min);

    return 0;
}
