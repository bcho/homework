#include <stdio.h>

float func(float eps);

int main()
{
    float eps = 0.0005;

    printf("%f", func(eps));

    return 0;
}

float func(float eps)
{
    float num, den, cur, i;

    for (num = 1, den = 3,i = 1, cur = 1 ;num / den >= eps;\
         i++, num *= i, den *= 2 * i + 1)
        cur += num / den;
    cur += num / den;

    return cur * 2;
}
