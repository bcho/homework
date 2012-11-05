#include <stdio.h>

int main()
{
    int a[6] = {1, 2, 3, 4, 5, 0}, n = 5, e = 0, i, j, is_swap;

    for (i = 0, is_swap = 0;i < n;i++)
        if (e <= a[i]) {
            for (j = n - 1;j >= i;j--)
                a[j + 1] = a[j];
            a[i] = e;
            is_swap = 1;
            break;
        }
    if (! is_swap)
        a[n] = e;

    for (i = 0;i <= n;i++)
        printf("%d ", a[i]);

    return 0;
}
