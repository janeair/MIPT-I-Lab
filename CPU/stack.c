#ifndef STACK_C_INCLUDED
#define STACK_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

stack_t stack_create (stack_t stack)
{
    stack.HeadElement = NULL;
    stack.StackSize = 0;
    return stack;
}

int stack_cmp (const stack_t* stack)
{
    int head = stack->HeadElement->numb;
    int headnext = stack->HeadElement->next->numb;
    if (head > headnext) return 1;
    else if (head == headnext) return 0;
         else return -1;
}

int peek (stack_t* stack)
{
    int sourse;
    sourse = stack->HeadElement->numb;
    return sourse;
}

void stack_FPRINT (const stack_t* stack, FILE* result)
{
    int i;
    unit* pointer = stack->HeadElement;
    fprintf( result, "STACK -> " );
    while (pointer != 0)
    {
        fprintf( result, "%d ", pointer->numb );
        pointer = pointer->next;
    }
    fprintf( result, "\nSTACKSIZE: %d\n", stack->StackSize );
}

void push ( stack_t* stack, int source )
{
    unit* pointer = (unit*) calloc(1, sizeof(unit));
    assert(pointer != 0);
    pointer->numb = source;
    if (stack->StackSize!=0)
    {
        pointer->next = stack->HeadElement;
    }
    else
    {
        pointer->next=0;
    }
    stack->HeadElement = pointer;
    stack->StackSize++;
}

int pop (stack_t* stack)
{
    int sourse;
    sourse = stack->HeadElement->numb;
    unit* pointer = stack->HeadElement->next;
    free(stack->HeadElement);
    stack->HeadElement = pointer;
    stack->StackSize--;
    return sourse;
}

void sqr (stack_t* stack)
{
    assert (stack != 0);
    int data = peek (stack);
    stack->HeadElement->numb*=data;
}

void sub (stack_t* stack)
{
    assert (stack != 0);
    int data;
    data = pop(stack);
    assert (stack != 0);
    stack->HeadElement->numb-=data;
}

void sdiv (stack_t* stack)
{
    assert (stack != 0);
    int data;
    data = pop(stack);
    assert (stack != 0);
    stack->HeadElement->numb/=data;
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
    while (stack->StackSize > 0) pop (stack);
    stack->HeadElement = NULL;
    stack = NULL;
}

#endif STACK_C_INCLUDED
