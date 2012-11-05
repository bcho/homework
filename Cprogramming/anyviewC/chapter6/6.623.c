#include <stdio.h>

int main()
{
    int n = 3, i, jmin, j = 2;
    int a[3][3] = {{1, 2, 3}, {1, -2, 3}, {1, 2, 3}};

    for (i = 0, jmin = 2 << 29;i < n;i++) {
        jmin = (jmin < a[i][j]) ? jmin : a[i][j];
    }

    printf("%d", jmin);

    return 0;
}
