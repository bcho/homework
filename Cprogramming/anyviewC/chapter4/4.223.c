#include <stdio.h>

// I know it's a bit strange... but it saves a lot of time
#define s(a) (a) * (a)

int main()
{
    int a, b, c, expr;

    scanf("%d %d %d", &a, &b, &c);

    // core
    expr = (a + c> b && b + c > a && a + b > c &&\
            (s(a) + s(b) == s(c) || s(a) + s(c) == s(c) || s(b) + s(c) == s(a)\
             )) ? 1 : 0;

    printf("%d", expr);

    return 0;
}
