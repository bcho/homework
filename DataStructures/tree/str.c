/* str.c: 字符串相关操作实现 */

#include "utils.h"
#include "str.h"

#include <stdlib.h>
#include <string.h>


char *str_copy(char *str)
{
    int size;
    char *buffer;

    size = strlen(str);
    buffer = (char *) Malloc(sizeof(char) * (size + 1));
    strncpy(buffer, str, size);
    buffer[size] = '\0';

    return buffer;
}

void str_copy_destory(char *str)
{
    free(str);
}

char *str_copyn(char *str, int n)
{
    char *buffer;

    buffer = Malloc(sizeof(char) * (n + 1));
    strncpy(buffer, str, n);
    buffer[n] = '\0';

    return buffer;
}

void str_copyn_destory(char *str)
{
    free(str);
}

int str_startswith(char *str, char prefix)
{
    return *str == prefix;
}

int str_endswith(char *str, char suffix)
{
    return *(str + strlen(str) - 1) == suffix;
}

int str_split(char *str, char delim, char ***rv)
{
    int i, tokens_count;
    char **tokens;
    char *c, *p;

    /* 计算分割段数 */
    /* 跳过在开头的分割字符 */
    for (c = str; *c == delim && *c != '\0'; c++)
        ;
    for (tokens_count = 0, c = c + 1; *c != '\0'; c++)
        if (*c == delim && *(c - 1) != delim)
            tokens_count = tokens_count + 1;
    if (*(c - 1) != delim)
        tokens_count = tokens_count + 1;

    /* 复制各个分割段 */
    tokens = (char **) Malloc(sizeof(char *) * tokens_count);
    for (c = str, i = 0; *c != '\0'; c++)
        if (*c != delim) {
            for (p = c; *p != delim && *p != '\0'; p++)
                ;
            tokens[i] = str_copyn(c, p - c);
            i = i + 1;
            c = p;
        }

    *rv = tokens;
    return tokens_count;
}

void str_split_destory(char **tokens, int count)
{
    int i;

    for (i = 0; i < count; i++)
        str_copyn_destory(tokens[i]);
    free(tokens);
}

char *str_replace(char *from, char *pattern, char *replace)
{
    char *rv;
    char *p, *q, *r;
    int from_len, count, rv_len, pattern_len, replace_len;

    from_len = strlen(from);
    pattern_len = strlen(pattern);
    replace_len = strlen(replace);

    for (count = 0, p = from;
         (q = strstr(p, pattern)) != NULL;
         p = q + pattern_len, count++)
        ;
    rv_len = from_len + count * (replace_len - pattern_len);

    rv = (char *) Malloc(sizeof(char) * (rv_len + 1));

    for (r = rv, p = from;
         (q = strstr(p, pattern)) != NULL;
         p = q + pattern_len) {
        memcpy(r, p, q - p);
        r = r + (q - p);
        memcpy(r, replace, replace_len);
        r = r + replace_len;
    }
    strcpy(r, p);

    return rv;
}

void str_replace_destory(char *str)
{
    free(str);
}
