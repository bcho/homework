#include <stdio.h>

int reverse_integer(int p);

int main()
{
    int p;

    printf("This program reverses the digits in an integer.\n"
           "Enter a positive integer: ");
    scanf("%d", &p);
    printf("The reversed number is %d", reverse_integer(p));

    return 0;
}

int reverse_integer(int p)
{
    int num;

    for (num = 0;p != 0;p /= 10) {
        num = num * 10 + p % 10;
    }

    return num;
}
