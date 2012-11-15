#include <stdio.h>
#include <stdlib.h>
#include "link.h"
#include "polynomial.h"

void print_node(node_t *n)
{
    printf("%dx^%d ", retrieve_coe(n), retrieve_exp(n));
}

polynomials_t build_polynomials(element_t exp[], element_t coe[], int n)
{
    if (n < 1) {
        printf("input wrong!");
        return NULL;
    }

    int i;
    polynomials_t p = make_list();
    pos_t insert_pos;
    insert(exp[0], coe[0], header(p));
    for (i = 1;i < n;i++) {
        insert_pos = find_pos(exp[i], p);
        insert(exp[i], coe[i], insert_pos);
    }
    return p;
}

void copy(polynomials_t src, polynomials_t dest)
{
    pos_t t, tail;
    for (t = header(src)->next, tail = header(dest);t;
         t = t->next, tail = tail->next)
        insert(retrieve_exp(t), retrieve_coe(t), tail);
}

int length(polynomials_t a)
{
    int i;
    pos_t cur;
    for (i = 0, cur = header(a)->next;cur;cur = cur->next, i++)
        ;
    return i;
}

/* find smallest n which n > exp */
pos_t find_pos(element_t exp, polynomials_t a)
{
    /* list is empty */
    if (is_empty(a))
        return header(a);
    /* is biggest */
    if (retrieve_exp(header(a)->next) < exp)
        return header(a);
    /* find suit position */
    pos_t cur;
    for (cur = header(a)->next;cur;cur = cur->next)
        if ((!is_last(cur) && retrieve_exp(cur) > exp && \
             retrieve_exp(cur->next) < exp) || is_last(cur)) {
            return cur;
        }
    return cur;
}

/* time complexity: O(M * (M + N)) = O(M^2 + MN) ~ O(M^2)
 * (M is shorter one's length)*/
polynomials_t add(polynomials_t a, polynomials_t b)
{
    pos_t cur, exp;
    polynomials_t l = make_list();
    copy((length(a) > length(b)) ? a : b, l);
    cur = header((length(a) > length(b)) ? b : a)->next;

    for (;cur;cur = cur->next) {
        exp = find(retrieve_exp(cur), l);
        if (exp != NULL) {
            exp->coe += cur->coe;
        } else {
            exp = find_pos(retrieve_exp(cur), l);
            insert(retrieve_exp(cur), retrieve_coe(cur), exp);
        }
    }
    return l;
}

/* time complexity: O(M * N * (M + N)) ~ O(M^2 * N)*/
polynomials_t multiply(polynomials_t a, polynomials_t b)
{
    if (is_empty(a) || is_empty(b)) {
        printf("input wrong!");
        return NULL;
    }

    pos_t i, j, pos;
    polynomials_t l = make_list();
    polynomials_t shorter, longer;
    element_t exp, coe;

    shorter = (length(a) > length(b)) ? b : a;
    longer = (length(a) > length(b)) ? a : b;

    for (i = header(shorter)->next;i;i = i->next)
        for (j = header(longer)->next;j;j = j->next) {
            exp = retrieve_exp(i) + retrieve_exp(j);
            coe = retrieve_coe(i) * retrieve_coe(j);
            pos = find(exp, l);
            if (pos != NULL) {
               pos->coe += coe; 
            } else {
                pos = find_pos(exp, l);
                insert(exp, coe, pos);
            }
        }
    return l;
}

/* how about O(MNlog(MN))? we can `find` with binarysearch) */
