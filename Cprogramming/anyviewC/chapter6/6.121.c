#include <stdio.h>

int main()
{
    int n = 20120826, i, len;
    char s[21], t[21];

    for (i = 0;n;i++, n /= 10)
        t[i] = n % 10 + '0';
    t[i] = '\0';
    len = i;
    for (i = 0;t[i] != '\0';i++)
        s[i] = t[len - i - 1];
    s[len] = '\0';

    printf("%s", s);

    return 0;
}
