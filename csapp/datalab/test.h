#ifndef TEST_H
#define TEST_H

#ifdef VERBOSE
#define TWO_VERBOSE_CHECK(name) printf("testcase %d for " name \
        ": %08x %08x, %08x %08x\n", i, x, y, a, b)
#define SINGLE_VERBOSE_CHECK(name) printf("testcase %d for " name \
        ": %08x, %08x %08x\n", i, x, a, b)
#else
#define TWO_VERBOSE_CHECK(name) ;
#define SINGLE_VERBOSE_CHECK(name) ;
#endif

#define TWO_TESTER(name, gex, gey, solution) \
    int test_##name(int testcases) \
    {\
        int i;\
        base_t x, y, a, b; \
        for (i = 0;i < (testcases);i++) { \
            x = (gex);\
            y = (gey);\
            a = (solution);\
            b = name(x, y);\
            TWO_VERBOSE_CHECK(#name);\
            assert(a == b);\
        }\
        return 1;\
    }

#define SINGLE_TESTER(name, ge, solution) \
    int test_##name(int testcases) \
    {\
        int i;\
        base_t x, a, b;\
        for (i = 0;i < (testcases);i++) {\
            x = (ge);\
            a = (solution);\
            b = name(x);\
            SINGLE_VERBOSE_CHECK(#name);\
            assert(a == b);\
        }\
        return 1;\
    }

#endif
