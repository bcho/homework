#include <stdio.h>

int main()
{
    int i, n, odd, even;

    scanf("%d", &n);

    for (i = 1, odd = 0, even = 0;i <= n;i++)
        if (i % 2) {
            odd += i;
        } else {
            even += i;
        }

    printf("sum of odd=%d  ", odd);
    printf("sum of even=%d", even);

    return 0;
}
