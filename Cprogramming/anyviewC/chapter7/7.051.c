#include <stdio.h>

#define lower(a) (((a) <= 'Z' && (a) >= 'A') ? ((a) - 'A' + 'a') : (a))

char s[] = "helloworld";
int c[26];

int main()
{
    int i;
    char *ch;

    for (i = 0;i < 26;i++)
        c[i] = 0;

    for (ch = s;*ch;ch++)
        c[lower(*ch) - 'a']++;

    for (i = 0;i < 26;i++)
        printf("%d ", c[i]);

    return 0;
}
