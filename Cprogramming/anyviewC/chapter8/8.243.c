#include <stdio.h>

int func(char *s, char *t)
{
    int i, j;

    for (i = 0;s[i];i++) {
        for (j = 0;t[j];j++)
            if (t[j] != s[i + j])
                break;
        if (!t[j])
            return i + 1;
    }

    return 0;
}

int main()
{
    printf("%d ", func("I am a student", "stu"));
    printf("%d", func("I am a student", "an"));

    return 0;
}
