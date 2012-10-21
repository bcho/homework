#include <stdio.h>

int main()
{
    int n, i, j, numer, denom;
    double pi2;

    scanf("%d", &n);

    pi2 = 1;
    for (i = 1;i <= n;i++) {
        numer = 1, denom = 1;
        for (j = 1;j <= i;j++)
            numer *= j, denom *= 2 * j + 1;
        //printf("%d %d\n", numer, denom);
        pi2 += (double) numer / (double) denom;

    }

    printf("%lf", pi2);

    return 0;
}
