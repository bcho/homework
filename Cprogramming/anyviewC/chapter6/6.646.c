#include <stdio.h>

int main()
{
    int n = 3, i;
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};
    double davg;

    for (i = 0, davg = 0;i < n;i++)
        davg += a[i][i];
    davg /= n;

    printf("%lf", davg);

    return 0;
}
