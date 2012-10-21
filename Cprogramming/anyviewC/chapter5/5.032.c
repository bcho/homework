#include <stdio.h>

int main()
{
    int n = 8, i;
    long f;

    for (i = 1,f = 1;i <= n;i++)
        f *= i % 2 == n % 2 ? i : 1;

    printf("%ld", f);

    return 0;
}
