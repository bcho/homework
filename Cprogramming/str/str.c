#include <stdlib.h>
#include <string.h>

#include "str.h"

#define WHITE_SPACES "\t "

static int is_white_spaces(char c)
{
    char *p;

    for (p = WHITE_SPACES;*p != 0;p++)
        if (*p == c)
            return 1;
    return 0;
}

char *trim(const char *raw)
{
    char *cleaned;
    int length, left, right;

    /* calculate trimed string's length */
    left = 0;
    right = strlen(raw) - 1;
    for (;left <= right;left++)
        if (!is_white_spaces(raw[left]))
            break;
    for (;right >= left;right--)
        if (!is_white_spaces(raw[right]))
            break;
    length = right - left + 2;  /* including tailing 0 */

    cleaned = malloc(sizeof(char) * length);
    if (!cleaned)
        return NULL;
    
    strncpy(cleaned, raw + left, length - 1);
    cleaned[length - 1] = 0;

    return cleaned;
}

char *join(const char **parts, int n, const char *delim)
{
    char *connected;
    int i;
    int parts_len[n], delim_len, len;

    /* calculate the connected length */
    delim_len = strlen(delim);
    for (i = 0, len = 0;i < n;i++) {
        parts_len[i] = strlen(parts[i]);
        len += parts_len[i];
    }
    /* counts of delimiters must be postive */
    len += ((n > 1) ? (n - 1) : (0)) * delim_len;

    connected = malloc(sizeof(char) * (len + 1));
    if (!connected)
        return NULL;

    connected[len] = 0;
    for (i = 0, len = 0;i < n;i++) {
        strncpy(connected + len, parts[i], parts_len[i]);
        len += parts_len[i];
        if (i < n - 1) {  /* there is no delimiter after the last part */
            strncpy(connected + len, delim, delim_len);
            len += delim_len;
        }
    }
    
    return connected;
}

char **split(const char *raw, const char *delim, int *count)
{
    char **splited;
    char *haystack, *next, *last, *c;
    int delim_len, part_len;
    size_t char_ptr_size;

    if (!raw)
        return NULL;

    *count = 0;
    last = (char *) (raw + strlen(raw));
    char_ptr_size = sizeof(char *);
    splited = malloc(char_ptr_size * 0);

    delim_len = strlen(delim);
    haystack = (char *) raw;
    while (1) {
        next = strstr(haystack, delim);

        if (!next)  /* copy the last part */
            next = last;

        /* get sub part's length */
        for (part_len = 0, c = haystack;c != next;c++, part_len++)
            ;

        /* copy sub part */
        splited = realloc(splited, (*count + 1) * char_ptr_size);
        splited[*count] = malloc(sizeof(char) * (part_len + 1));
        strncpy(splited[*count], haystack, part_len);
        splited[*count][part_len] = 0;
        *count += 1;

        if (c == last)  /* end after copy the last part here */
            break;

        haystack = next + delim_len;
    }

    return splited;
}
