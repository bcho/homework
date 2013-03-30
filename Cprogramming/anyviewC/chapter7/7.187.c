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
    return 1 - 1 / (float) (n + 1);
}
