#include <stdio.h>

int main()
{
    unsigned long a = 0x12ac;
    unsigned long b;

    b = ~a;

    printf("a=%lx\nb=%lx\n", a, b);

    return 0;
}
