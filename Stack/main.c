#include <stdio.h>
#include "stack.h"
#include "stack.c"

int main()
{
    stack_t stack = stack_create (stack);
    push (&stack, 15);
    push (&stack, 2);
    mul (&stack);
    printf ("%lg", pop (&stack));
    return 0;
}
