#include <stdio.h>

int main()
{
    int n = 3, i = 2, imax, j;
    int a[3][3] = {{1, 2, 3}, {1, -2, 3}, {1, 2, 3}};

    for (j = 0, imax= -2 << 29;j < n;j++) {
        imax = (imax > a[i - 1][j]) ? imax : a[i - 1][j];
    }

    printf("%d", imax);

    return 0;
}
