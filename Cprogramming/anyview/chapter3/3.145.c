#include <stdio.h>

int main()
{
    float f, g, h;

    f = -2.345;
    g = 6.789;
    h = (f + g);
    h *= h * h;

    printf("%f\n", h);

    return 0;
}
