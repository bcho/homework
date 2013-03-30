int func(char *s, char c)
{
    int i;

    for (i = 0;*s;s++, i++)
        if (*s == c)
            return i + 1;

    return 0;
}
