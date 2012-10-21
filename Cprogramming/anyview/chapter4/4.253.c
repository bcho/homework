#include <stdio.h>

int main()
{
    unsigned int a = 34, b = 34, c = 78, d, e, f;

    // did you mean `&` / `|` instead of `&&` / `||`?
    d = a && b;
    e = a || c;
    f = a && c;

    printf("%d && %d = %d\n", a, b, d);
    printf("%d || %d = %d\n", a, c, e);
    printf("%d && %d = %d\n", a, b, f);

    return 0;
}
