#include "utils.h"
#include "config.h"

#include <stdlib.h>

void *
u_sbrk(intptr_t increments)
{
    static void *__brk;
    static void *__brk_start;
    static int initiated = 0;

    void *old_brk;

    if (!initiated) {
        initiated = 1;
        __brk = malloc(MEM_SIZE);
        if (__brk == NULL)
            goto fail;
        __brk_start = __brk;
    }

    if (increments == 0)
        return __brk;

    old_brk = __brk;
    // FIXME range check
    if ((intptr_t) old_brk + increments < (intptr_t) __brk_start
        || (intptr_t) old_brk + increments > (intptr_t) __brk_start + MEM_SIZE)
        goto fail;

    // We just implement brk here.
    __brk = old_brk + increments;

    return old_brk;

fail:
    return (void *) -1;
}

size_t
u_getline(char **lineptr, size_t *n, FILE *stream)
{
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
    	return -1;
    }
    if (stream == NULL) {
    	return -1;
    }
    if (n == NULL) {
    	return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
    	return -1;
    }
    if (bufptr == NULL) {
    	bufptr = malloc(128);
    	if (bufptr == NULL) {
    		return -1;
    	}
    	size = 128;
    }
    p = bufptr;
    while(c != EOF) {
    	if ((p - bufptr) > (size - 1)) {
    		size = size + 128;
    		bufptr = realloc(bufptr, size);
    		if (bufptr == NULL) {
    			return -1;
    		}
    	}
    	*p++ = c;
    	if (c == '\n') {
    		break;
    	}
    	c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}
