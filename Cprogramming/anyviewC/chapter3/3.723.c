#include <stdio.h>

int main()
{
    int a, b, c;
    
    scanf("%d", &a);
    scanf("%d", &b);
    c = a * a + b * b;

    printf("%d^2+%d^2=%d\n", a, b, c);

    return 0;
}
