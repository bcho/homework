#include <stdio.h>

int main()
{
    int n = 3, i, dmax;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, dmax = -2 << 29;i < n;i++)
        dmax = (dmax > a[i][i]) ? dmax : a[i][i];

    printf("%d", dmax);

    return 0;
}
