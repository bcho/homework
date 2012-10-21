#include <stdio.h>

int main()
{
    int a, b;

    a = 34;
    b = 56;

    a += b; 
    b *= a;

    printf("a=%d b=%d\n", a, b);

    return 0;
}
