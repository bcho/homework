#include <stdio.h>

int prime(int n);
int f(int i);

int main()
{
    printf("%d", f(18));

    return 0;
}

int prime(int n)
{
    int i;
    
    // use n / 2 here, but sqrt(n) should be better
    for (i = 2;i <= n / 2;i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int f(int i)
{
    int j;

    for (j = 2;j <= i / 2;j++)
        if (prime(j) && prime(i - j))
            return j;

    return -1;
}
