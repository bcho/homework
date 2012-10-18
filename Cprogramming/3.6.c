/* 3.6
 * 请编写程序将 "China" 译成密码，密码规律是：用原来的字母后面第 4 个字母代替
 * 原来的字母。 (China -> Glmre)
 * */

#include <stdio.h>
#include <ctype.h>

#define SHIFT 4

char encrypt(char c);

int main()
{
    char c;

    while ((c = getchar()) != EOF) {
        printf("%c", encrypt(c));
    }

    return 0;
}

char encrypt(char c)
{
    char start_c;

    if (isalpha(c)) {
        if (islower(c)) {
            start_c = 'a';
        } else {
            start_c = 'A';
        }

        return ((c - start_c) + SHIFT) % 26 + start_c;
    } else {
        return c;
    }
}
