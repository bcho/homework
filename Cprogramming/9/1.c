#include <stdio.h>
#include <stdlib.h>

#include "st.h"

struct st *del_list(struct st *source, struct st *target);

int main()
{
    struct st *a, *b;

    build(&a);
    build(&b);
    print(b);
    b = del_list(a, b);
    print(b);

    destory(a);
    destory(b);

    return 0;
}

struct st *del_list(struct st *source, struct st *target)
{
    struct st dummy, *prev, *p, *q;

    dummy.s = target;
    for (p = source;p != NULL && dummy.s != NULL;p = p->s)
        for (q = dummy.s, prev = &dummy;q != NULL;)
            if (q->num == p->num) {
                prev->s = q->s;
                free(q);
                q = prev->s;
            } else {
                prev = q;
                q = q->s;
            }
    return dummy.s;
}
