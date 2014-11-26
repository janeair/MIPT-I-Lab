#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>

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

stack_t stack_create (stack_t stack);
int stack_cmp (const stack_t* stack);
int peek (stack_t* stack);
void stack_FPRINT (const stack_t* stack, FILE* result);
void push ( stack_t* stack, int source );
int pop (stack_t* stack);
void add (stack_t* stack);
void mul (stack_t* stack);
void sub (stack_t* stack);
void sdiv (stack_t* stack);
void sqr (stack_t* stack);
void stack_destr (stack_t* stack);

#endif STACK_H_INCLUDED
