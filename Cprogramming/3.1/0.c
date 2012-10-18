#include <stdio.h>
#include <math.h>

double pow(double a, double b);

int main()
{
    double p, r;
    int n;

    r = 0.09;
    n = 10;

    // p = (1 + r) ^ n
    p = pow((1 + r), (double) n);

    printf("it\'s %lf times after %d years.\n", p, n);

    return 0;
}
