#include <stdio.h>
#include <stdlib.h>

#define MAX 1024
#define lower(A) ((A) >= 'A' && (A) <= 'Z') ? ((A) - 'A' + 'a') : (A)

static int cmp(const char *a, const char *b);

int main()
{
    char str[MAX], tmp[MAX], c;
    int length, i;

    length = 0;
    while ((c = getchar()) != EOF)
        tmp[length++] = c;
    tmp[length] = '\0';

    for (i = 0;i < length;i++)
        str[i] = lower(tmp[length - i - 1]);
    str[length] = '\0';
    printf("%s\n", str);

    qsort(str, length, sizeof(char), cmp);

    printf("%s\n", str);

    return 0;
}

static int cmp(const char *a, const char *b)
{
    return (*a > *b);
}
