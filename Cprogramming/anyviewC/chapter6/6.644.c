#include <stdio.h>

int main()
{
    int n = 3, j = 1, i; 
    int a[3][3] = {{1, 2, 4}, {1, -2, 3}, {1, 2, 3}};
    double javg;

    for (i = 0, javg = 0;i < n;i++)
        javg += a[i][j];
    javg /= n;

    printf("%lf", javg);

    return 0;
}
