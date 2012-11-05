#include <stdio.h>

int main()
{
    int n = 3, i, dsum;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, dsum = 0;i < n;i++)
        dsum += a[i][i];

    printf("%d", dsum);

    return 0;
}
