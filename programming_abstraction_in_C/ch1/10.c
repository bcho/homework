#include <stdio.h>

double pi(int n);

int main()
{
    printf("the pi is %lf using the first 10,000 terms in Leibniz's series",
            pi(10000));

    return 0;
}

double pi(int n)
{
    double ret;
    int i;
    
    for (i = 1, ret = 0;i <= n;i++)
        ret += (-1) * ((i % 2) ? -1 : 1) / (double) (2 * i - 1);

    return ret * 4;
}
