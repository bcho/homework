#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hello.h"

#define BASE_LENGTH 8

char *hello(const char *name)
{
    size_t length;
    char *greeting;
   
    length = strlen(name) + BASE_LENGTH + 1;

    greeting = malloc(sizeof(char) * length);
    if (greeting == NULL) {
        return NULL;
    }
    snprintf(greeting, length, "Hello, %s!", name);

    return greeting;
}
