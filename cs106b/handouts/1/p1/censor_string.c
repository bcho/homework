#include <stdlib.h>
#include <string.h>

char *CensorString(char *text, char *remove)
{
    char *ret, *i;
    int j;

    ret = malloc(sizeof(char) * 1);
    for (j = 0, i = text;*i != '\0';i++) {
        if (strchr(remove, *i) == NULL) {
            ret[j++] = *i; 
            ret = realloc(ret, (strlen(ret) + 1) * sizeof(char));
        }
    }
    ret[j] = '\0';

    return ret;
}
