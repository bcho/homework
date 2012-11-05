#include <stdio.h>

int main()
{
    int n = 3, i, jmax, j = 2;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, jmax = -2 << 29;i < n;i++) {
        jmax = (jmax > a[i][j]) ? jmax : a[i][j];
    }

    printf("%d", jmax);

    return 0;
}
