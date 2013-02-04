#include <stdio.h>

#include "count_letters.h"

void CountLetters(char *filename)
{
    FILE *stream;
    int count[26], i;

    for (i = 0;i < 26;i++)
        count[i] = 0;
    stream = fopen(filename, "r");
    for (;fscanf(stream, "%c", &i) != EOF;) {
        if (i <= 'z' && i >= 'a' )
            count[i - 'a']++;
        if (i <= 'Z' && i >= 'A')
            count[i - 'A']++;
    }
    for (i = 0;i < 26;i++)
        printf("%c:%d\n", i + 'a', count[i]);
}
