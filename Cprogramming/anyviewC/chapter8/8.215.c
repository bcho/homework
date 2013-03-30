int func(char *s, char c)
{
    int count;

    for (count = 0;*s;s++)
        if (*s == c)
            count++;

    return count;
}
