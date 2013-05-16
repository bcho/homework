#include <stdio.h>
#include <string.h>

int cmpstr(char *s1, char *s2);

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("%s str1 str2\n", argv[0]);
        return 1;
    }
    printf("%d", cmpstr(argv[1], argv[2]));

    return 0;
}

int cmpstr(char *s1, char *s2)
{
    int i, lena, lenb;

    lena = strlen(s1); lenb = strlen(s2);
    for (i = 0;i < lena && i < lenb;i++)
        if (s1[i] > s2[i])
            return 1;
        else if (s1[i] < s2[i])
            return -1;
    if (lena > lenb)
        return 1;
    if (lena < lenb)
        return -1;
    return 0;
}
