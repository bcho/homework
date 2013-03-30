#define LOWER(a) (((a) <= 'Z' && (a) >= 'A') ? ((a) - 'A' + 'a') : (a))

void func(char *s, char *t)
{
    while ((*t++ = LOWER(*s)))
        s++;
}
