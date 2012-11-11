/* 
 * Weeks 2 problem 2
 *
 * 输入 c1, c2, c3, 只使用一句表达式和条件表达式（可嵌套）将
 * 三者按从小到大顺序排序。
 *
 * */

#include <stdio.h>

int main()
{
    char c1, c2, c3;
    scanf("%c %c %c", &c1, &c2, &c3);

    (c1 > c2) ? (c1 ^= c2 ^= c1 ^= c2) : 0,
        (c1 > c3) ? (c1 ^= c3 ^= c1 ^= c3) : 0,
        (c2 > c3) ? (c2 ^= c3 ^= c2 ^= c3) : 0;
    
    printf("%c %c %c", c1, c2, c3);

    return 0;
}
