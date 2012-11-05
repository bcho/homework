#include <stdio.h>

int main()
{
    int a[5][5] = {{17, 24, 1, 8, 15},
                   {23, 5, 7, 14, 16},
                   {4, 6, 13, 20, 22},
                   {10, 12, 19, 21, 3},
                   {11, 18, 25, 2, 9}};
    int n = 5, i, j, sum, is_magic, tmp1, tmp2, tmp3, tmp4;

    is_magic = 1;
    for (i = 0, sum = 0;i < n;i++)
        sum += a[0][i];

    for (i = 0, tmp3 = 0, tmp4 = 0;i < n;i++) {
        for (j = 0, tmp1 = 0, tmp2 = 0;j < n;j++) {
            tmp1 += a[i][j];
            tmp2 += a[j][i];
        }
        if (tmp1 != sum || tmp2 != sum) {
            is_magic = 0;
            break;
        }
        tmp3 += a[i][i];
        tmp4 += a[i][n - i - 1];
    }
    if (tmp3 != sum || tmp4 != sum)
        is_magic = 0;

    printf("%d", is_magic);

    return 0;
}
