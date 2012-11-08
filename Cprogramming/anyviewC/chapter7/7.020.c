#include <stdio.h>

int change(int n);

int main()
{
    printf("%d", change(40));

    return 0;
}

int change(int n)
{
    int ret;

    // 10 = 1 * 10 = 10 * 1 = 5 * 2 = 5 * 1 + 1 * 5 (4)
    // 5 = 5 * 1 = 1 * 5                            (2)
    // 1 = 1 * 1                                    (1)
    if (n < 5)
        ret = 1;
    else
        ret = n / 10 * 4 + n % 10 / 5 * 2;

    return ret;
}
