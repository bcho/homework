#include <stdio.h>

int main()
{
    int a[5] = {1, 2, 3, 4, 5};
    int n = 5, index, min = 2 << 29, i;

    for (i = 0;i < n;i++) {
        if (a[i] < min) min = a[i], index = i;
    }
    a[0] ^= a[index] ^= a[0];

    printf("%d %d", index, min);

    return 0;
}
