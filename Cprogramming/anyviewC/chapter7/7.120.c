#include <stdio.h>

int n = 20120826;
char s[20];

int main()
{
    int i;

    for (i = 0;n > 0;n /= 10)
        s[i++] = n % 10 + '0';

    printf("%s", s);

    return 0;
}
