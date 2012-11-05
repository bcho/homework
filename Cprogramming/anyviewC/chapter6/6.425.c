#include <stdio.h>

int main()
{
    int a[100] = {2, 3}, n = 6, i;

    for (i = 2;i < n;i++) {
        a[i] = (a[i - 1] - a[i - 2]) * 2;
        printf("%d ", a[i]);
    }

    return 0;
}
