#ifndef POLYNOMIALS_H
#define POLYNOMIALS_H

#include "link.h"

polynomials_t add(polynomials_t a, polynomials_t b);
polynomials_t multiply(polynomials_t a, polynomials_t b);

pos_t find_pos(element_t exp, polynomials_t a);
polynomials_t build_polynomials(element_t exp[], element_t coe[], int n);
void print_node(node_t *n);
#endif
