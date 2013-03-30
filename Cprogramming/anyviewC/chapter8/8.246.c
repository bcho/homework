#include <stdio.h>

int func(char *c, char (*w)[10]);
void _strncpy(char *dest, char *src, int n);

int main()
{
    int i, count;
    char w[10][10];

    printf("%d\n", (count = func("def abc cde", w)));
    for (i = 0;i < count;i++)
        printf("%s ", w[i]);

    return 0;
}

void _strncpy(char *dest, char *src, int n)
{
    int i;

    for (i = 0;i < n;i++)
        *(dest + i) = *(src + i);
    dest[n] = 0;
}

int func(char *c, char (*w)[10])
{
    int i, start, end;

    for (start = 0;c[start] == ' ';start++)
        ;
    for (end = start, i = 0;c[end];end++) {
        if (c[end] == ' ') {
            _strncpy(w[i++], c + start, end - start);
        }
        if (c[end] != ' ' && c[end - 1] == ' ')
            start = end;
    }
    _strncpy(w[i++], c + start, end - start);

    return i;
}
