#include <stdio.h>

int main()
{
    char s[] = "abcijkabcedxyzuvwx";
    int c[26] = {0}, i;

    for (i = 0;s[i] != '\0';i++)
        c[s[i] - 'a'] ++;

    for (i = 0;i < 25;i++)
        printf("%d ", c[i]);
    printf("%d\n", c[25]);

    return 0;
}
