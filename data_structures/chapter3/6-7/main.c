#include <stdio.h>
#include "polynomial.h"

#define sep printf("\n")

int main()
{
    int exp[6] = {4, 3, 2, 1, 0, 2};
    int coe[6] = {1, 3, 4, 5, 2, 12};
    polynomials_t a = build_polynomials(exp, coe, 6);
    polynomials_t b = build_polynomials(coe, exp, 6);
    polynomials_t c = add(a, b);
    traversal(print_node, a);
    sep;
    traversal(print_node, b);
    sep;
    traversal(print_node, c);
    sep;
    c = multiply(a, b);
    traversal(print_node, c);

    return 0;
}
