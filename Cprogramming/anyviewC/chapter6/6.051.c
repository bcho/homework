#include <stdio.h>

int main()
{
    char s[] = "AbcijKaBcedXyzuvwx";
    int c[26] = {0}, i;

    for (i = 0;s[i] != '\0';i++) {
        if (s[i] - 'A' > 26)
            c[s[i] - 'a']++;
        else
            c[s[i] - 'A']++;
    }

    for (i = 0;i < 25;i++)
        printf("%d ", c[i]);
    printf("%d\n", c[25]);

    return 0;
}
