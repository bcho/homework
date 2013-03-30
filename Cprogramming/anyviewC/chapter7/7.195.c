#include <stdio.h>

float func(int m, int n);

int main()
{
    int m, n;

    scanf("%d %d", &m, &n);
    printf("%f", func(m, n));

    return 0;
}

int fact(int a)
{
    int f;

    for (f = 1;a > 1;f *= a, a--)
        ;
    return f;
}

float func(int m, int n)
{
    return fact(m) / (float) (fact(n) * fact(m - n));
}
