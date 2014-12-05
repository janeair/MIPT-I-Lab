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

int stack_OK (const stack_t* stack)
{
    if (stack != 0 && stack->StackSize >= 0 && (stack->HeadElement != 0 || stack->StackSize == 0) )
        return 0;
    else if (stack == 0)
        {
            printf("- 404 Stack Not Found -\n");
            return 1;
        }
        else if (stack->StackSize < 0)
            {
                printf("- StackSize Out Of Range -\n");
                return 2;
            }
            else
            {
                printf("- Invalid Pointer -\n");
                return 3;
            }
}

double peek (stack_t* stack)
{
    int sourse;
    if ( stack_OK(stack) != 0 ) return 0.5;
    if (stack->StackSize == 0)
    {
        printf("- Sorry, Stack Is Empty -\n");
        return -0.5;
    }
    sourse = stack->HeadElement->numb;
    return sourse;
}

void stack_PRINT (const stack_t* stack)
{
    assert(stack != 0);
    unit* pointer = stack->HeadElement;
    if ( stack_OK(stack) != 0 ) return;
    printf("Your Stack\n StackSize %d\n Elements -> ", stack->StackSize);
    while (pointer != 0)
    {
        if (stack->StackSize == 0) { printf("- Stack Isn't Clear -\n"); return; }
        printf("%d ", pointer->numb);
        pointer = pointer->next;
    }
    return;
}

void push ( stack_t* stack, int source )
{
    if ( stack_OK(stack) != 0 ) return;
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
    return;
}

double pop (stack_t* stack)
{
    int sourse;
    if ( stack_OK(stack) != 0 ) return 0.5;
    if (stack->StackSize == 0)
    {
        printf("- Sorry, Stack Is Empty -\n");
        return -0.5;
    }
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
    return;
}

void mul (stack_t* stack)
{
    assert (stack != 0);
    int data;
    data = pop(stack);
    assert (stack != 0);
    stack->HeadElement->numb*=data;
    return;
}

void stack_destr (stack_t* stack)
{
    while (stack->StackSize >= 0) pop (stack);
    stack->HeadElement = NULL;
    stack = NULL;
    return;
}

#endif STACK_C_INCLUDED
