#include "kmp.h"

#include <string.h>
#include <stdio.h>


static void build_patrial_match(char *partial, int *table)
{
    int pp, i;

    table[0] = 0;
    for (i = 1, pp = 0; i < strlen(partial); i++)
        if (partial[pp] == partial[i]) {
            pp = pp + 1;
            table[i] = pp;
        } else {
            table[i] = 0;
            pp = 0;
        }
}

int kmp_match(char *haystack, char *needle)
{
    int i, j, hl, nl, pl;

    hl = strlen(haystack);
    nl = strlen(needle);

    int partial[nl];

    build_patrial_match(needle, partial);

    for (i = 0, j = 0; i < hl && hl - i >= nl;)
        if (haystack[i + j] == needle[j]) {
            j = j + 1;
            if (j == nl)
                return i;
        } else {
            if (j == 0) {
                i = i + 1;
            } else {
                i = i + j - partial[j - 1];
                j = partial[j - 1];
            }
        }

    return -1;
}
