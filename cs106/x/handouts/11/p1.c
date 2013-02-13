#include <stdio.h>

#include "map.h"
#include "str.h"

#define DELIM_BEGIN "{{"
#define DELIM_END "}}"

char *generateStory(char *storyTemplate, struct map_t* data);

int main()
{
    char *template = "{{ actor }} gave {{ restaurant }} a {{ rating }}-star review.";
    struct map_t *map = map_create();
    map_set(map, "actor", "Mike Vernal");
    map_set(map, "restaurant", "The French Laundry");
    map_set(map, "rating", "5");

    printf("%s\n", generateStory(template, map));

    return 0;
}

char *generateStory(char *storyTemplate, struct map_t* data)
{
    char *story, *key, *value;
    int start, end;

    story = str_copy(storyTemplate);
    while ((start = str_find_str(story, DELIM_BEGIN)) != -1) {
        end = str_find_str(story, DELIM_END);
        key = str_substr(story, start + str_length(DELIM_BEGIN),\
                end - start - str_length(DELIM_BEGIN));
        str_trim(&key);
        value = map_get(data, key);
        // printf("%s %s\n", key, value);
        str_replace(&story, start, end - start + str_length(DELIM_END), value);
    }
    return story;
}
