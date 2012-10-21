#include <stdio.h>

int main()
{
    int a, b, c ,d, e;

    a = 511;
    b = 246;
    c = 257;
    d = 495;
    e = (a + b) / ((b - c) * (a - d));

    printf("(%d+%d)/((%d-%d)*(%d-%d))=%d\n", a, b, b, c, a, d, e);
    
    return 0;
}
