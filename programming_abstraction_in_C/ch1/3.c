#include <stdio.h>

int main()
{
    int i, n, sum;

    printf("input n: ");
    scanf("%d", &n);

    for (i = 0, sum = 0;i <= n;i++)
        sum += i;

    printf("the sum of the numbers between 1 and %d is %d.", n, sum);

    return 0;
}
