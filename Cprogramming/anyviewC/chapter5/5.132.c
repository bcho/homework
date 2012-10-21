#include <stdio.h>

int main()
{
    int i, sum, n;

    scanf("%d", &n);

    for (i = 0;i <= n;i += 7)
        sum += i;

    printf("sum = %d", sum);

    return 0;
}
