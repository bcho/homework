#include <stdio.h>

void func(char s[], char t[], int n);

int main()
{
    char s[] = "time", t[100];

    func(s, t, 4);

    printf("%s", t);

    return 0;
}

void func(char s[], char t[], int n)
{
    int i;

    for (i = 0;i < n;i++)
        t[i] = s[n - i - 1];
    t[n] = '\0';

    return;
}
