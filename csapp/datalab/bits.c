#include <stdio.h>

#include "bits.h"

base_t
bitNor(base_t x, base_t y)
{
    return ~x & ~y;
}

base_t
bitXor(base_t x, base_t y)
{
    return ~(x & y) & ~(~x & ~y);
}

int
isNotEqual(base_t x, base_t y)
{
    return !!(x ^ y);
}

base_t
getByte(base_t x, int n)
{
    return 0xFF & (x >> (n << 3));
}

base_t
copyLSB(base_t x)
{
    return ((signed int) (x & 1)) << 31 >> 31;
}

base_t
logicalShift(base_t x, int n)
{
    return ((signed int) ((x >> 31) & 1) << 31 >> n) ^ (x >> n);
}

int
bitCount(base_t x)
{

}

base_t
bang(base_t x)
{

}

base_t
leastBitPos(base_t x)
{

}

int
tmax(void)
{
    return (unsigned int) ~0 >> 1;
}
