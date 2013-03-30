void func(char *s, int n, char *t)
{
    int i;

    for (i = n;(i--) && (*t++ = *s++);)
        ;
    t[n] = 0;
}
