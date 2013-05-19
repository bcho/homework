#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find(char *dict[], int size, const char *needle, char ***result);

int main()
{
    char *dict[] = {
        "hello world",
        "hello string",
        "heworldllo",
        "hello",
        "he"
    };
    char **result;
    int i, foundc;
    
    foundc = find(dict, sizeof(dict) / sizeof(dict[0]), "hell", &result);

    for (i = 0;i < foundc;i++)
        printf("%s\n", result[i]);

    free(result);

    return 0;
}

inline void insert(char **dest, int size, char *key)
{
    dest = realloc(dest, sizeof(char *) * (size + 1));
    dest[size] = key;
}

int find(char *dict[], int size, const char *needle, char ***result)
{
    int i, j, foundc;
    int needle_len, key_len;
    int sub_match;

    *result = malloc(sizeof(char *) * 0);
    needle_len = strlen(needle);
    for (i = 0, foundc = 0;i < size;i++) {
        key_len = strlen(dict[i]);

        if (key_len == needle_len && strcmp(needle, dict[i]) == 0) {
            insert(*result, foundc, dict[i]);
            foundc++;
            continue;
        }
        if (key_len > needle_len) {
            if (strstr(dict[i], needle)) {
                insert(*result, foundc, dict[i]);
                foundc++;
                continue;
            }

            for (j = 0, sub_match = 0;j < needle_len;j++)
                if (strchr(dict[i], needle[j]))
                    sub_match++;
            if (sub_match > needle_len / 2) {
                insert(*result, foundc, dict[i]);
                foundc++;
                continue;
            }
        }
    }

    return foundc;
}
