#include <stdio.h>

int func(int a, int b);

int main()
{
    printf("%d", func(45, 12));
    return 0;
}

int func(int a, int b)
{
    return a % 100 / 10 * 1000 + a % 10 * 10 + b % 100 / 10 * 100 + b % 10;
}
