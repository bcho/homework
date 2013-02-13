#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "str.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))

static char *allocate(int length)
{
    char *buf;

    assert(length > 0);
    buf = malloc(sizeof(char) * length);
    assert(buf != NULL);

    return buf;
}

void str_free(char *string)
{
    assert(string != NULL);
    free(string);
}

int str_length(char *string)
{
    return (int) strlen(string);
}

char str_at(char *string, int pos)
{
    int length;

    for (length = str_length(string);pos < 0;pos += length)
        ;
    assert(pos < length);
    return *(string + pos);
}

char *str_copy(char *src)
{
    int length;
    char *new;

    length = str_length(src);
    new = allocate(length + 1);
    memcpy(new, src, sizeof(char) * (length + 1));
    return new;
}

int str_cmp(char *a, char *b)
{
    int i, a_len, b_len;

    a_len = str_length(a);
    b_len = str_length(b);
    for (i = 0;i < min(a_len, b_len);i++)
        if (a[i] < b[i])
            return -1;
        else if (a[i] > b[i])
            return 1;
    if (a_len < b_len)
        return -1;
    else if (a_len > b_len)
        return 1;
    return 0;
}

char *str_concat(char *a, char *b)
{
    int new_len, a_len, b_len, i;
    char *new;

    a_len = str_length(a);
    b_len = str_length(b);
    new_len = a_len + b_len;
    new = allocate(new_len + 1);
    for (i = 0;i < new_len;i++)
        if (i < a_len)
            new[i] = a[i];
        else
            new[i] = b[i - a_len];
    new[new_len] = '\0';
    return new;
}

void str_append(char **string, char *part)
{
    /* just drop the old copy? is that ok? */
    *string = str_concat(*string, part);
}

int str_find_char(char *haystack, char needle)
{
    int i;

    for (i = 0;i < str_length(haystack);i++)
        if (haystack[i] == needle)
            return i;
    return -1;
}

int str_find_str(char *haystack, char *needle)
{
    int i, j, haystack_len, needle_len;

    haystack_len = str_length(haystack);
    needle_len = str_length(needle);
    for (i = 0;i < haystack_len;i++) {
        for (j = 0;j < needle_len;j++)
            if (*(haystack + i + j) != *(needle + j))
                break;
        if (j == needle_len)
            return i;
    }
    return -1;
}

char *str_substr(char *string, int start, int length)
{
    int new_len, str_len;
    char *new;

    assert(start >= 0);
    str_len = str_length(string);
    if (start > str_len)
        new_len = 0;
    else if (start + length > str_len)
        new_len = str_len - start + 1;
    else
        new_len = length;
    new = allocate(new_len + 1);
    memcpy(new, string + start, sizeof(char) * (new_len + 1));
    new[new_len] = '\0';

    return new;
}

void str_insert(char **a, int start, char *b)
{
    int new_len, a_len, b_len;
    char *new;

    a_len = str_length(*a);
    b_len = str_length(b);
    new_len = a_len + b_len;
    new = allocate(new_len + 1);
    memcpy(new, *a, sizeof(char) * start);
    memcpy(new + start, b, sizeof(char) * b_len);
    memcpy(new + start + b_len, *a + start,\
            sizeof(char) * (a_len - start + 1));
    /* just drop the old copy? is that ok? */
    *a = new;
}

void str_replace(char **a, int start, int length, char *b)
{
    int new_len, a_len, b_len;
    char *new;

    a_len = str_length(*a);
    b_len = str_length(b);
    new_len = a_len - length + b_len;
    new = allocate(new_len + 1);
    memcpy(new, *a, sizeof(char) * start);
    memcpy(new + start, b, sizeof(char) * b_len);
    memcpy(new + start + b_len, *a + start + length,\
            sizeof(char) * (a_len - start - length + 1));
    /* just drop the old copy? is that ok? */
    *a = new;
}

void str_trim(char **string)
{
    char *start, *end;

    start = str_copy(*string);
    while (isspace(*start))
        start++;
    /* all spaces */
    if (*start == '\0')
        return;

    end = start + str_length(start) - 1;
    while (end > start && isspace(*end))
        end--;

    *(end + 1) = '\0';

    *string = start;
}
