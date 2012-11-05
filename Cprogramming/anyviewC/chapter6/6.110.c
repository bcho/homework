#include <stdio.h>

int main()
{
    char s[] = "68abcdEFGhijkLM86";
    int i;

    for (i = 0;s[i] != '\0';i++)
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] = s[i] - 'a' + 'A';

    printf("%s", s);

    return 0;
}
