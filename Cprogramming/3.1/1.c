#include <stdio.h>

double int_pow(double a, int b);

int main()
{
    double p, r;
    int n;
    
    r = 0.09;
    n = 10;

    // p = (1 + r) ^ n
    p = int_pow((1 + r), n);

    printf("it\'s %lf times. after %d years.\n", p, n);

    return 0;
}

/* For calculating the integer times of a */
double int_pow(double a, int b)
{
    int i;
    double ret;
    for (i = 0, ret = 1.0;i < b;i++, ret *= a)
        ;

    return ret;
}
