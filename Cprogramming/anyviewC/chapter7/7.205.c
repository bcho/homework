#include <stdio.h>

int func(int n);

int main()
{
    int n;

    scanf("%d", &n);
    printf("%d", func(n));

    return 0;
}

int func(int n)
{
    int sum, i;

    for (i = 2, sum = 0;i < n;i++)
        if (n % i == 0)
            sum += i;

    return sum;
}
