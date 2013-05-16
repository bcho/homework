#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 2

void change_sort(char *s1, int m, char *s2);

int main()
{
    char *s1 = "hello world!";
    char s2[100];

    change_sort(s1, N, s2);
    printf("%s", s2);

    return 0;
}

int cmp(const void *a, const void *b)
{
    return *((char *) a) - *((char *) b);
}

void change_sort(char *s1, int m, char *s2)
{
    char *src, *dest;

    for (src = s1 + m, dest = s2;(*dest++ = *src++);)
        ;
 
    qsort(s2, sizeof(char) * strlen(s2), sizeof(char), cmp);
}
