#include <stdio.h>

double mypow(double x, int n);

int main()
{
    double a;
    int n;

    scanf("%lf %d", &a, &n);
    printf("%lf\n", mypow(a, n));

    return 0;
}

double mypow(double x, int n)
{
    double p;

    if (n == 1)
        return x;
    p = mypow(x, n / 2);
    if (n % 2)
        return p * p * x;
    return p * p;
}
