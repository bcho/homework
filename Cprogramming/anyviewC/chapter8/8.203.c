int func(char *s)
{
    int count;

    for (count = 0;*s;s++, count++)
       ;
    
    return count; 
}
