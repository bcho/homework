#include <stdlib.h>

#include "st.h"

struct st *sort_list(struct st *head);

int main()
{
    struct st *a;

    build(&a);
    print(a);
    a = sort_list(a);
    print(a);

    destory(a);
    return 0;
}

static void *
find_mid(void *list, void *(*next)(void *))
{
    void *slow, *fast;

    if (list == NULL)
        return NULL;

    slow = list; fast = list;
    while (next(fast) != NULL && next(next(fast)) != NULL) {
        slow = next(slow);
        fast = next(next(fast));
    }

    return slow;
}

static void *
merge(void *left, void *right, void *(*next)(void *), 
      void (*set_next)(void *, void *),
      int (*cmp)(void *, void *), int reverse)
{
    void *head, *prev, *p;

    head = NULL;
    p = head;
    while (left != NULL && right != NULL) {
        if (cmp(left, right) >= 0 && !reverse) {
            p = left;
            left = next(left);
        } else {
            p = right;
            right = next(right);
        }

        if (head == NULL)
            head = p;
        else
            set_next(prev, p);
        prev = p;
    }
    if (left == NULL)
        set_next(p, right);
    else
        set_next(p, left);

    return head;
}

inline static void *
_sort(void *list, void *(*next)(void *), void (*set_next)(void *, void *),
      int (*cmp)(void *, void *), int reverse)
{
    void *mid, *left, *right;

    if (list == NULL || next(list) == NULL)
        return list;

    left = list;
    mid = find_mid(list, next);
    right = next(mid);
    set_next(mid, NULL);

    return merge(_sort(left, next, set_next, cmp, reverse),
                 _sort(right, next, set_next, cmp, reverse),
                 next, set_next, cmp, reverse);
}

void
link_sort(void **list, void *(*next)(void *), void (*set_next)(void *, void *),
          int (*cmp)(void *, void *), int reverse)
{
    *list = _sort(*list, next, set_next, cmp, reverse);
}

int cmp(void *a, void *b)
{
    return ((struct st *) b)->num - ((struct st *) a)->num;
}

void *next(void *a)
{
    return ((struct st *) a)->s;
}

void set_next(void *a, void *b)
{
    ((struct st*) a)->s = (struct st*) b;
}

struct st *sort_list(struct st *head)
{
    link_sort((void **) &head, next, set_next, cmp, 0);
    
    return head;
}
