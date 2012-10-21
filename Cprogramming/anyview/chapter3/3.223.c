#include <stdio.h>

int main()
{
    unsigned int a, b, c;

    a = 0x123a;
    b = 0x1100;
    c = a & b;

    printf("%x & %x = %x\n", a, b, c);

    return 0;
}
