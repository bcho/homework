#include <stdio.h>

int main()
{
    int n = 3, i, jsum, j = 1; 
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, jsum = 0;i < n;i++)
        jsum += a[i][j];

    printf("%d", jsum);

    return 0;
}
