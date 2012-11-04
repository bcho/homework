#include <stdio.h>

int main()
{
    long n;
    int d, num, m = 9;
    num = 0;
    scanf("%ld %d", &n, &d);

    do {
        if (n % 10 == d) num ++;
        if (n % 10 < m) m = num % 10;
        n /= 10;
    } while (n);

    printf("num=%d, min=%d", num, m);

    return 0;
}
