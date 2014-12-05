#ifndef STACK_CPU_H_INCLUDED
#define STACK_CPU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "stack.c"

typedef struct register_t
{
    int data;
    int full;
}
register_t;
// TYPE OF REGISTER

typedef struct cpu_t
{
    register_t AX;
    register_t BX;
    stack_t cpu;
}
cpu_t;
// STRUCT OF STACK CPU

register_t clear (register_t reg)
{
    reg.data = 0;
    reg.full = 0;
}
// CLEARS THE REGISTER

#endif // STACK_CPU_H_INCLUDED
