#include <stdio.h>

int main()
{
    int n = 3, i, dmin;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, dmin = 2 << 29;i < n;i++)
        dmin = (dmin < a[i][i]) ? dmin : a[i][i];

    printf("%d", dmin);

    return 0;
}
