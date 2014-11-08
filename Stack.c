#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct unit
{
    int numb;
    struct unit *next;
}
unit;

typedef struct stack_t
{
    unit* HeadElement;
    int StackSize;
}
stack_t;


void push ( stack_t* stack, int source ) // push new element
{
    assert(stack != 0);
    unit* pointer = (unit*) malloc(sizeof(unit));
    assert(pointer != 0);
    pointer->numb = source;
    if (stack->StackSize!=0) { pointer->next = stack->HeadElement; }
    else { pointer->next=0; }
    stack->HeadElement = pointer;
    stack->StackSize++;
}

int pop (stack_t* stack) // pop head element
{
    int sourse;
    assert(stack != 0);
    sourse = stack->HeadElement->numb;
    unit* pointer = stack->HeadElement->next;
    free(stack->HeadElement);
    stack->HeadElement = pointer;
    stack->StackSize--;
    return sourse;
}

void add (stack_t* stack)
{
    assert (stack != 0);
    int data;
    data = pop(stack);
    assert (stack != 0);
    stack->HeadElement->numb+=data;
}

void mul (stack_t* stack)
{
    assert (stack != 0);
    int data;
    data = pop(stack);
    assert (stack != 0);
    stack->HeadElement->numb*=data;
}

void stack_destr (stack_t* stack)
{
    assert (stack != 0);
    while (stack->StackSize > 0) pop (stack);
    stack = NULL;
}

int main()
{
    stack_t stack = {0,0}; // create stack
    push (&stack, 2);
    push (&stack, 3);
    mul (&stack);
    printf("%d", pop(&stack));
    stack_destr (&stack);
    push (&stack, 2);
    printf("\n%d", pop(&stack));
    return 0;
}
