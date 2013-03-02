#include <stdio.h>

int main()
{
    int i, n, sum;

    printf("input n: ");
    scanf("%d", &n);

    for (i = 1, sum = 0;i < 2 * n;i += 2)
        sum += i;

    printf("%d", sum);

    return 0;
}
