#include <stdio.h>

int main()
{
    float a, b, c, d;

    a = 111.234;
    b = 23.456;
    c = a * b;
    d = a / b;

    printf("%.3f*%.3f=%f\n", a, b, c);
    printf("%.3f/%.3f=%f\n", a, b, d);

    return 0;
}
