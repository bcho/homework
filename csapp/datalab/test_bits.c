#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#include "bits.h"

#define VERBOSE
#define TESTCASES 5
#include "test.h"

inline base_t get_random(void);

TWO_TESTER(bitNor, get_random(), get_random(), ~(x | y));
TWO_TESTER(bitXor, get_random(), get_random(), x ^ y);
TWO_TESTER(isNotEqual, get_random(), get_random(), x != y);
TWO_TESTER(getByte, get_random(), get_random() % 4, (x >> (y * 8)) & 0xFF);
SINGLE_TESTER(copyLSB, get_random(), (x & 1) ? ~0 : 0);
TWO_TESTER(logicalShift, get_random(), get_random() % 32, x / (1 << y));

int
main()
{
    srand(time(NULL));

    test_bitNor(TESTCASES);
    test_bitXor(TESTCASES);

    if (!isNotEqual(5, 5)) {
        test_isNotEqual(TESTCASES);
    }

    test_getByte(TESTCASES);
    test_copyLSB(TESTCASES);
    test_logicalShift(TESTCASES);

    assert(tmax() == INT_MAX);

    return 0;
}

inline base_t
get_random()
{
    return rand();
}
