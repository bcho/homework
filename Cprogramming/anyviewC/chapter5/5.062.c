#include <stdio.h>

int main()
{
    int sum = 0, n = 0;
    
    do {
        scanf("%d", &n);
        sum += n;
    } while (n != 0);

    printf("sum = %d", sum);

    return 0;
}
