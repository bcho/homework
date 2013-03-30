#include <stdio.h>

int n = 20120826;
char s[20];

int main()
{
    sprintf(s, "%d", n);

    printf("%s", s);

    return 0;
}
