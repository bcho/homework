#include <stdio.h>

void func(char s[]);

int main()
{
    char s[] = "******";

    func(s);
    printf("%s", s);

    return 0;
}

void func(char s[])
{
    int i, count, len;

    for (count = 0;s[count] == '*';count++)
        ;
    for (i = count, len = 0;s[i];i++, len++)
        s[i - count] = s[i];
    for (i = 0;i < count;i++)
        s[len + i] = '*';
}
