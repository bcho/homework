#include <stdio.h>

int main()
{
    float a, b, c, d;

    a = 1.234;
    b = 23.456;
    c = a + b;
    d = a -b;

    printf("%f+%f=%f\n", a, b, c);
    printf("%f-%f=%f\n", a, b, d);

    return 0;
}
