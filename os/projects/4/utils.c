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
