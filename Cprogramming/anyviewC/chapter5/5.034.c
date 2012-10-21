#include <stdio.h>

int main()
{
    int n = -5, i, t;
    double f;

    for (i = 1, t = 1;i <= -n + 1;i++)
        t *= i;
    f = 1 / (double) t;

    printf("%lf", f);

    return 0;
}
