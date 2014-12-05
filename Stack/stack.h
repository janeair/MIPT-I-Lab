#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>

typedef struct unit
{
    int numb;
    struct unit *next;
}
unit;
// STRUCT OF STACK ELEMENT

typedef struct stack_t
{
    unit* HeadElement;
    int StackSize;
}
stack_t;
// STRUCT OF STACK
// HEADELEMENT - LAST ELEMENT IN STACK

stack_t stack_create (stack_t stack);
// CREATES EMPTY STACK

int stack_OK (const stack_t* stack);
// CHECKS THE CONDITION OF STACK
// RETURNS:
// 0 : EVERYTHING IS OK
// 1 : STACK NOT FOUND
// 2 : INVALID STACKSIZE
// 3 : INVALID POINTER

double peek (stack_t* stack);
// RETURNS DATA FROM HEADELEMENT
// 0.5 : SMT GOES WRONG
// -0.5 : EMPTY STACK

void stack_PRINT (const stack_t* stack);
// PRINTS STACK STARTING FROM HEADELEMENT

void push ( stack_t* stack, int source );
// PUSHES NEW ELEMENT IN STACK

double pop (stack_t* stack);
// RETURNS DATA FROM HEADELEMENT AND THAN DELETES IT
// 0.5 : SMT GOES WRONG
// -0.5 : EMPTY STACK

void add (stack_t* stack);
// ADDS TWO LAST NUMBERS IN STACK

void mul (stack_t* stack);
// MULTIPLIES TWO LAST NUMBERS IN STACK

void stack_destr (stack_t* stack);
// DESTROYS STACK AT ALL

#endif STACK_H_INCLUDED
