#include <stdio.h>

void func(char *str, char *key);

int main()
{
    char str[] = "helloworld";
    char *key = "helloworld";

    func(str, key);
    printf("%s", str);

    return 0;
}

#define SQR(x) ((x) * (x))

void func(char *str, char *key)
{
    int salt;
    char *c;

    for (salt = 0, c = key;*c;c++)
        salt += SQR(*c) % 128;
    for (c = str;*c;c++)
        if (*c >= 'a' || *c <= 'z')
            *c = *c % 128 + salt;
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int min(int x, int y, int z)
{
    return MIN(MIN(x, y), z);
}
