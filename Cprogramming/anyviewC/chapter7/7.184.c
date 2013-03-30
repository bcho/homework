#include <stdio.h>

float func(int n);

int main()
{
    int n;

    scanf("%d", &n);
    printf("%f", func(n));

    return 0;
}

float func(int n)
{
    int i;
    float s, frac;

    for (s = 0, i = 1, frac = 0;i <= n;frac += i, s += 1 / frac, i++)
        ;

    return s;
}
