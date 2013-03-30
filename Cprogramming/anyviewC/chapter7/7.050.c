#include <stdio.h>

void func(char *str);

int main()
{
    char s[] = "helloworld";

    func(s);
    printf("%s", s);

    return 0;
}

void func(char *str)
{
    int pos, i;
    char *c;

    for (c = str, pos = 0, i = 0;*c;c++, i++)
        if (*c < str[pos])
            pos = i;
    for (i = pos, *c = str[pos];i > 0;i--)
        str[i] = str[i - 1];
    str[0] = *c;
}
