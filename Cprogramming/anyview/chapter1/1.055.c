#include <stdio.h>

void main()
{
    int a, b, c, max;
    scanf("%d %d %d", &a, &b, &c);

    max = a > b ? a : b;
    max = max > c ? max : c;

    printf("最大数为：%d", max);
}
