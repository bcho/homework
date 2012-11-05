#include <stdio.h>

int main()
{
    int n = 3, d2max, i;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, d2max= -2 << 29;i < n;i++)
        d2max = (d2max > a[i][i]) ? d2max : a[i][i];
    for (i = 0;i < n;i++)
        d2max = (d2max > a[i][n - i - 1]) ? d2max : a[i][n - i - 1];

    printf("%d", d2max);

    return 0;
}
