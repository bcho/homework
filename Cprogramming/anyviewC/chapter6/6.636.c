#include <stdio.h>

int main()
{
    int n = 3, d2min, i;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, d2min= 2 << 29;i < n;i++)
        d2min = (d2min < a[i][i]) ? d2min : a[i][i];
    for (i = 0;i < n;i++)
        d2min = (d2min < a[i][n - i - 1]) ? d2min : a[i][n - i - 1];

    printf("%d", d2min);

    return 0;
}
