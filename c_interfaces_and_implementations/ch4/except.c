#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "except.h"

#define T  except_t

except_frame *except_stack = NULL;

void except_raise(const T *e, const char *file, int line)
{
    except_frame *p = except_stack;
    assert(e);
    if (p == NULL) {
        fprintf(stderr, "Uncaught exception");
        if (e->reason)
            fprintf(stderr, " %s", e->reason);
        else
            fprintf(stderr, " at 0x%p", e);
        if (file && line > 0)
            fprintf(stderr, " raised at %s:%d\n", file, line);
        fprintf(stderr, "aborting...\n");
        fflush(stderr);
        abort();
    }
    p->exception = e;
    p->file = file;
    p->line = line;
    except_stack = except_stack->prev;
    longjmp(p->env, except_raised);
}
