#include <stdio.h>

char *match(char *s, char c);

int main()
{
    char *ret = match("abcz", 'z');

    if (ret)
        printf("%s", ret);
    else
        printf("Not found");

    return 0;
}

char *match(char *s, char c)
{
    while (*s != c && *s) {
        s++;
    }
    if (*s != c)
        return NULL;
    else
        return s;
}
