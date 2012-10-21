#include <stdio.h>

int main()
{
    int i, n, tmp, j;
    double e, x, denom;

    scanf("%d", &n);
    scanf("%lf", &x);

    tmp = 1;
    for (i = 1, e = 1;i <= n;i++) {
        tmp *= i;
        denom = 1;
        for (j = 1;j <= i;j++)
            denom *= x;
        e +=  denom / tmp;
    }

    printf("%lf", e);

    return 0;
}
