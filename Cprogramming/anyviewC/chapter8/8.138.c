#include <stdio.h>

int func(int *x, int *y)
{
    if (*x > *y) {
        *x = *x ^ *y; *y = *x ^ *y; *x = *x ^ *y;
        return 1;
    }
    return 0;
}

int main()
{
    int a, b;

    a = 15; b = 5;
    func(&a, &b);
    printf("%d %d", a, b);

    return 0;
}
