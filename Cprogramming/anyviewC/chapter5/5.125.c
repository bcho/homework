#include <stdio.h>

int main()
{
    int num, sum = 0;

    scanf("%d", &num);

    do {
        if (num / 100 % 10 == 3)
            sum += num;
        scanf("%d", &num);
    } while (num);

    printf("sum = %d", sum);

    return 0;
}
