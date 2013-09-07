#include "assert.h"

#include "bitvector.h"

int
main()
{
    init_vector();
    assert(get_vector(0) == 0u);
    assert(get_vector(120) == 0u);

    set_vector(21, 1);
    assert(get_vector(21) == 1u);
    set_vector(32, 1);
    assert(get_vector(32) == 1u);

    return 0;
}
