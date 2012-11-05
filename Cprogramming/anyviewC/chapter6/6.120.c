#include <stdio.h>

int main()
{
    int n = 20120826, i;
    char s[21];

    for (i = 0;n;i++, n /= 10)
        s[i] = n % 10 + '0';
    s[i] = '\0';

    printf("%s", s);

    return 0;
}
