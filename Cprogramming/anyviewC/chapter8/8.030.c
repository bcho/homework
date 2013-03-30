#include <stdio.h>
#include <math.h>

int prime(int n)
{
    int i;

    for (i = 2;i<= sqrt(n);i++)
        if (n % i == 0)
            return 0;
    return 1;
}

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int f(int i)
{
    int j;

    for (j = 2;j <= i / 2;j++)
        if (prime(j) && prime(i - j))
            return j;
    return i;
}

int main()
{
    printf("%d", f(16));

    return 0;
}
