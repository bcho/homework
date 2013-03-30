#define UPPER(a) (((a) <= 'z' && (a) >= 'a') ? ((a) - 'a' + 'A') : (a))

void func(char *s, char *t)
{
    while ((*t++ = UPPER(*s)))
        s++;
}
