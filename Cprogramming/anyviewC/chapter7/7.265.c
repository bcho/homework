#include <stdio.h>

void func(char s[], char t[]);

int main()
{
    char s[] = "ABCDE123456";
    char t[20];

    func(s, t);
    printf("%s", t);

    return 0;
}

void func(char s[], char t[])
{
    int i, j;

    for (i = 0, j = 0;s[j] != '\0';j++)
        if (j % 2 == 0 && s[j] % 2 == 0)
            t[i++] = s[j];
    t[i] = 0;
}
