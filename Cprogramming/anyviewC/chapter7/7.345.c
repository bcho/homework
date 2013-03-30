#include <stdio.h>

int func(char s[]);

int main()
{
    char s[] = "helloworld";

    printf("%d", func(s));

    return 0;
}

int func(char s[])
{
    int i, count = 0;

    for (i = 0, count = 1;s[i] == ' ';i++, count = 0)
        ;
    for (;s[i];i++)
        if (s[i] != ' ' && s[i - 1] == ' ')
            count++;

    return count;
}
