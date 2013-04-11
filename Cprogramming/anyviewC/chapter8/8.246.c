#include <stdio.h>

int func(char *c, char (*w)[10]);
void _strncpy(char *dest, char *src, int n);

int main(int argc, char **argv)
{
    int i, count;
    char w[10][10];

    printf("%d\n", (count = func(argv[1], w)));
    for (i = 0;i < count;i++)
        printf("%s ", w[i]);

    return 0;
}

int _isalpha(char c)
{
    if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
        return 1;
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
    char *cur;

    for (start = 0;!_isalpha(c[start]) && c[start] != 0;start++)
        ;
    for (cur = c + start, end = start, i = 0;c[end] != 0;end++) {
        if (!_isalpha(c[end]) && _isalpha(c[end - 1])) {
            _strncpy(w[i++], cur, end - start);
        } else if (_isalpha(c[end]) && !_isalpha(c[end - 1])) {
            start = end;
            cur = c + start;
        }
    }
    if (_isalpha(c[end - 1])) {
        _strncpy(w[i++], cur, end - start);
    }

    return i;
}
