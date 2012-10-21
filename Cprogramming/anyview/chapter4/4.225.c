#include <stdio.h>

int main()
{
    int a, b, c, expr;

    scanf("%d %d %d", &a, &b, &c);

    // core
    // really awkard...
    int max = a > b ? (a > c ? a : c)  : (b > c ? b : c);
    int a1 = a == max ? (b == max ? c : b ) : a;
    int a2 = a + b + c - max - a1;
    expr = (a + c > b && b + c > a && a + b > c &&\
            a1 * a1 + a2 * a2 > max * max) ? 1 : 0;

    printf("%d", expr);

    return 0;
}
