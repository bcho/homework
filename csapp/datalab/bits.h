#ifndef BITS_H
#define BITS_H

typedef unsigned int base_t;

// ~(x | y) using only & and ~
base_t bitNor(base_t x, base_t y);

// ^ using only & and ~
base_t bitXor(base_t x, base_t y);

// x != y?
int isNotEqual(base_t x, base_t y);

base_t getByte(base_t x, int n);

// 构造 32 位数字
// >> 对 signed 会产生 arithmetic shift
base_t copyLSB(base_t x);

// 构造 32 - n 位数字，>> 后做 ^
base_t logicalShift(base_t x, int n);

int bitCount(base_t x);

base_t bang(base_t x);

base_t leastBitPos(base_t x);

int tmax(void);

#endif
