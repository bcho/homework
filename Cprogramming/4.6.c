/* 4.6
 * 有一个函数
 *      x       (x < 1)
 * y =  2x - 1  (1 <= x < 10)
 *      3x - 11 (x >= 10)
 * 写程序，输入 x 的值，输出 y 相应的值。
 * */

#include <stdio.h>

int main()
{
    int x, y;

    scanf("%d", &x);

    if (x < 1)
        y = x;
    if (x >= 1 && x < 10)
        y = 2 * x - 1;
    if (x >= 10)
        y = 3 * x - 11;

    printf("%d", y);

    return 0;
}
