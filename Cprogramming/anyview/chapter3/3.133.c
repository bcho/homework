#include <stdio.h>

int main()
{
    float f, g, h;

    f = 12.345;
    g = 67.89;
    h = f * g;

    printf("%.3f*%.2f=%f\n", f, g, h);

    return 0;
}
