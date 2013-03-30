#include <stdio.h>
#include <math.h>

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
    int i, ret;

    for (i = 8, ret = 0;i < n;i++)
        if (i % 3 == 0 && i % 7 == 0)
            ret += i;

    return sqrt(ret);
}
