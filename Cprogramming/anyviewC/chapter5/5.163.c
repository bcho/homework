#include <stdio.h>

int main()
{
    int i, n, tmp;
    double e;

    scanf("%d", &n);

    tmp = 1;
    for (i = 1, e = 1;i <= n;i++) {
        tmp *= i;
        e += 1 / (double) tmp;
    }

    printf("%lf", e);

    return 0;
}
