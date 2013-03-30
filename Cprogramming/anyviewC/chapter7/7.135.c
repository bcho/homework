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
    int len, tmp;

    for (tmp = n, len = 1;tmp > 0;tmp /= 10, len *= 10)
        ;

    return n % (len / 10);
}
