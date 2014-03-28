#include "naive.h"

#include <string.h>

int naive_match(char *haystack, char *needle)
{
    int i, j;
    int hl, nl;

    hl = strlen(haystack);
    nl = strlen(needle);

    if (nl > hl)
        return -1;

    for (i = 0; i < hl && hl - i >= nl; i++) {
        for (j = 0; j < nl; j++)
            if (needle[j] != haystack[i + j])
                break;
        if (j == nl)
            return i;
    }

    return -1;
}
