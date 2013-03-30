#include <stdio.h>

int func(int n, int *a, int x);

int main()
{
    int a[10] = {5, 6, 3, 0, -4, 8, 9, -6, 8, -7};

    printf("%d ", func(10, a, 5));
    printf("%d ", func(10, a, 8));
    printf("%d ", func(10, a, 4));

    return 0;
}

int func(int n, int *a, int x)
{
    int i;

    for (i = 0;i < n;i++)
        if (*(a + i) == x)
            return i + 1;
    return 0;
}
