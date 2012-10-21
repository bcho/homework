#include <stdio.h>

int main()
{
    int a, b, c;

    a = 567;
    b = 18;
    c = 5;

    a /= b;
    b %= c;

    printf("%d %d %d\n", a, b, c);

    return 0;
}
