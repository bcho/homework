#include <stdio.h>
#include "circularly_link.h"

#define sep printf("\n")

circularly_link_t build_joseph_list(int length);
element_t kill(int m, int n);
void print_node(pos_t n);

int main()
{
    printf("%d", kill(1, 10002));
    sep;
    return 0;
}

void print_node(pos_t n)
{
    printf("%d,", retrieve(n));
}

circularly_link_t build_joseph_list(int length)
{
    circularly_link_t l = make_list();
    int i;
    for (i = 1;i <= length;i++) {
        insert(i, current(l), l);
        forward(l);
    }
    /* current point to first person */
    reset(l);
    forward(l);
    return l;
}

/* time complexity: O(M*N + M*(N - 1) ~ O(MN)) */
element_t kill(int m, int n)
{
    circularly_link_t l = build_joseph_list(n);
    int counter = 0;
    element_t ret;
    while (l->length > 1) {
        if (counter == m) {
            //printf("killed %d\n", retrieve(current(l)));
            pop(current(l), l);
            counter = 0;
        } else {
            forward(l);
            counter++;
        }
    }
    ret = retrieve(current(l));
    dispose_list(l);
    return ret;
}
