#include "brackets.h"
#include "stack.h"

#include <string.h>

int brackets_single_check(char *stream)
{
    int counter;
    char *c;

    for (c = stream, counter = 0; *c != '\0' && counter >= 0; c++)
        if (*c == '(') {
            counter = counter + 1;
        } else if (*c == ')') {
            counter = counter - 1;
            if (counter < 0)
                return 0;
        }

    return (counter == 0);
}

int brackets_check(char *stream)
{
    struct stack *brackets;
    char *c;
    char top;

    brackets = stack_init(strlen(stream));
    if (brackets == NULL)
        return 0;

    for (c = stream; *c != '\0'; c++)
        if (*c == '(' || *c == '[' || *c == '{')
            stack_push(brackets, *c);
        else if (*c == ')' || *c == ']' || *c == '}') {
            top = stack_top(brackets);
            if (top == 0)
                return 0;

            if (top != '(' && *c == ')')
                return 0;
            if (top != '[' && *c == ']')
                return 0;
            if (top != '{' && *c == '}')
                return 0;

            stack_pop(brackets);
        }

    return stack_is_empty(brackets);
}
