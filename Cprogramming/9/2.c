#include <stdio.h>
#include <stdlib.h>

#include "st.h"

struct st *inverted_list(struct st *head);

int main()
{
    struct st *a;

    build(&a);
    print(a);
    a = inverted_list(a);
    print(a);

    destory(a);

    return 0;
}

struct st *inverted_list(struct st *head)
{
    struct st dummy, *next;

    for (dummy.s = NULL;head != NULL;head = next) {
        next = head->s;
        head->s = dummy.s;
        dummy.s = head;
    }
    return dummy.s;
}
