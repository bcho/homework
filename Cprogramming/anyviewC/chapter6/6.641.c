#include <stdio.h>

int main()
{
    int n = 3, i = 1, isum, j; 
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (j = 0, isum = 0;j < n;j++)
        isum += a[i][j];

    printf("%d", isum);

    return 0;
}
