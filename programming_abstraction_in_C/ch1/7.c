#include <stdio.h>
#include <math.h>

int is_perfect(int num);

int main()
{
    int i;

    for (i = 1;i <= 9999;i++)
        if (is_perfect(i))
            printf("%d\n", i);

    return 0;
}

int is_perfect(int num)
{
    int i, sum;

    for (i = 2, sum = 1;i < sqrt(num);i++)
        if (num % i == 0)
            sum += i + num / i;

    return (sum == num && num != 1);
}
