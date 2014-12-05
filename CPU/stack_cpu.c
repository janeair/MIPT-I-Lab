#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "stack.c"
#include "stack_cpu.h"
#include "assembler.h"

int main ()
{
    // DECLARE STACK CPU
    cpu_t stack_cpu;

    // IN & OUT FILES
    FILE* source;
    FILE* result;
    const char* pathin = "source.txt";
    const char* pathout = "output.txt";
    const char* pathresult = "result.txt";

    // ARRAY OF COMMANDS
    int command[1000];
    int curr = 0;
    int last_cmd = 0;

    // ASSEMLY (USES ASSEMBLER.H)
    assembler(pathin, pathout);

    source = fopen(pathout,"r");
    assert(source != 0);
    result = fopen(pathresult,"w");
    assert(result != 0);

    // CREATE STACK
    stack_cpu.cpu = stack_create(stack_cpu.cpu);
    stack_cpu.AX = clear(stack_cpu.AX);
    stack_cpu.BX = clear(stack_cpu.BX);

    // READ COMMANDS FROM ASSEMBLER FILE
    while( !feof(source) )
    {
        curr++;
        fscanf( source, "%d ", &command[curr]);
    }

    last_cmd = curr;
    curr = 1;

    // EXECUTION

    while( command[curr] != END && curr <= last_cmd )
    {
        switch (command[curr])
        {
            case CPOP:
            {
                if (stack_cpu.cpu.StackSize != 0)
                {
                    pop(&stack_cpu.cpu);
                        curr++;
                }
                else
                {
                    fprintf( result, "RROCESS FAILED\nCOMMAND: %d\n", curr);
                    fprintf( result, "RETURNED 1 (S)");
                    exit(0);
                }
            }
            break;

            case CPOPA:
            {
                if (stack_cpu.cpu.StackSize != 0)
                {
                    stack_cpu.AX.data = pop(&stack_cpu.cpu);
                    stack_cpu.AX.full = 1;
                    curr++;
                }
                else
                {
                    fprintf( result, "RROCESS FAILED\nCOMMAND: %d\n", curr);
                    fprintf( result, "RETURNED 1 (AX)");
                    exit(0);
                }
            }
            break;

            case CPOPB:
            {
                if (stack_cpu.cpu.StackSize != 0)
                {
                    stack_cpu.BX.data = pop(&stack_cpu.cpu);
                    stack_cpu.BX.full = 1;
                    curr++;
                }
                else
                {
                    fprintf( result, "RROCESS FAILED\nCOMMAND: %d\n", curr);
                    fprintf( result, "RETURNED 1 (BX)");
                    exit(0);
                }
            }
            break;

            case CPUSH:
            {
                curr++;
                push(&stack_cpu.cpu, command[curr]);
                curr++;
            }
            break;

            case CPUSHA:
            {
                if (stack_cpu.AX.full != 0)
                {
                    push(&stack_cpu.cpu, stack_cpu.AX.data);
                    stack_cpu.AX = clear(stack_cpu.AX);
                    curr++;
                }
                else
                {
                    fprintf( result, "RROCESS FAILED\nCOMMAND: %d\n", curr);
                    fprintf( result, "RETURNED 1 (AX)");
                    exit(0);
                }
            }
            break;

            case CPUSHB:
            {
                if (stack_cpu.BX.full != 0)
                {
                    push(&stack_cpu.cpu, stack_cpu.BX.data);
                    stack_cpu.BX = clear(stack_cpu.BX);
                    curr++;
                }
                else
                {
                    fprintf( result, "RROCESS FAILED\nCOMMAND: %d\n", curr);
                    fprintf( result, "RETURNED 1 (BX)");
                    exit(0);
                }
            }
            break;

            case CPUSHAX:
            {
                curr++;
                stack_cpu.AX.data = command[curr];
                stack_cpu.AX.full = 1;
                curr++;
            }
            break;

            case CPUSHBX:
            {
                curr++;
                stack_cpu.BX.data = command[curr];
                stack_cpu.BX.full = 1;
                curr++;
            }
            break;

            case CADD:
            {
                if (stack_cpu.cpu.StackSize > 1)
                {
                    add(&stack_cpu.cpu);
                    curr++;
                }
                else
                {
                    fprintf( result, "RROCESS FAILED\nCOMMAND: %d\n", curr);
                    fprintf( result, "RETURNED 2");
                    exit(0);
                }
            }
            break;

            case CMUL:
            {
                if (stack_cpu.cpu.StackSize > 1)
                {
                    mul(&stack_cpu.cpu);
                    curr++;
                }
                else
                {
                    fprintf( result, "RROCESS FAILED\nCOMMAND: %d\n", curr);
                    fprintf( result, "RETURNED 2");
                    exit(0);
                }
            }
            break;

            case CSUB:
            {
                if (stack_cpu.cpu.StackSize > 1)
                {
                    sub(&stack_cpu.cpu);
                    curr++;
                }
                else
                {
                    fprintf( result, "RROCESS FAILED\nCOMMAND: %d\n", curr);
                    fprintf( result, "RETURNED 2");
                    exit(0);
                }
            }
            break;

            case CDIV:
            {
                if (stack_cpu.cpu.StackSize > 1)
                {
                    sdiv(&stack_cpu.cpu);
                    curr++;
                }
                else
                {
                    fprintf( result, "RROCESS FAILED\nCOMMAND: %d\n", curr);
                    fprintf( result, "RETURNED 2");
                    exit(0);
                }
            }
            break;

            case CSQR:
            {
                if (stack_cpu.cpu.StackSize != 0)
                {
                    sqr(&stack_cpu.cpu);
                    curr++;
                }
                else
                {
                    fprintf( result, "RROCESS FAILED\nCOMMAND: %d\n", curr);
                    fprintf( result, "RETURNED 1 (S)");
                    exit(0);
                }
            }
            break;

            case CMOVEAB:
            {
                if (stack_cpu.AX.full == 1)
                {
                    stack_cpu.BX.data = stack_cpu.AX.data;
                    stack_cpu.BX.full = 1;
                    stack_cpu.AX = clear(stack_cpu.AX);
                    curr++;
                }
                else
                {
                    fprintf( result, "RROCESS FAILED\nCOMMAND: %d\n", curr);
                    fprintf( result, "RETURNED 1 (AX)");
                    exit(0);
                }
            }
            break;

            case CMOVEBA:
            {
                if (stack_cpu.BX.full == 1)
                {
                    stack_cpu.AX.data = stack_cpu.BX.data;
                    stack_cpu.AX.full = 1;
                    stack_cpu.BX = clear(stack_cpu.BX);
                    curr++;
                }
                else
                {
                    fprintf( result, "RROCESS FAILED\nCOMMAND: %d\n", curr);
                    fprintf( result, "RETURNED 1 (BX)");
                    exit(0);
                }
            }
            break;

            case CJMP:
            {
                curr++;
                curr = command[curr];
            }
            break;

            case CJE:
            {
                curr++;
                if (stack_cmp(&stack_cpu.cpu) == 0)
                    curr = command[curr];
                else
                    curr++;
            }
            break;

            case CJNE:
            {
                curr++;
                if (stack_cmp(&stack_cpu.cpu) != 0)
                    curr = command[curr];
                else
                    curr++;
            }
            break;

            case CJL:
            {
                curr++;
                if (stack_cmp(&stack_cpu.cpu) == -1)
                    curr = command[curr];
                else
                    curr++;
            }
            break;

            case CJNL:
            {
                curr++;
                if (stack_cmp(&stack_cpu.cpu) != -1)
                    curr = command[curr];
                else
                    curr++;
            }
            break;

            case CJG:
            {
                curr++;
                if (stack_cmp(&stack_cpu.cpu) == 1)
                    curr = command[curr];
                else
                    curr++;
            }
            break;

            case CJNG:
            {
                curr++;
                if (stack_cmp(&stack_cpu.cpu) != 1)
                    curr = command[curr];
                else
                    curr++;
            }
            break;

            case CCALL:
            {

            }
            break;

            default:
            {
                fprintf( result, "RROCESS FAILED\nCOMMAND: %d\n", curr);
                fprintf( result, "RETURNED 3");
                exit(0);
            }
        }
    }

    // OUT OF RANGE COMMANDS ARRAY

    if (curr > last_cmd)
    {
        fprintf( result, "RROCESS FAILED\n");
        fprintf( result, "RETURNED 4");
        exit(0);
    }

    // PROGRAM ENDS WITHOUT ERRORS WITH "END" CODE
    // OUTPUT DATA FROM CPU

    fprintf( result, "PROCESS RETURNED 0\nCPU:\n" );
    stack_FPRINT (&stack_cpu.cpu, result);
    fprintf( result, "REGISTERS:\n");
    if (stack_cpu.AX.full == 1) fprintf( result, "AX: %d", stack_cpu.AX.data );
    if (stack_cpu.BX.full == 1) fprintf( result, "BX: %d", stack_cpu.BX.data );

    // CPU SHUT DOWN

    fclose(source);
    fclose(result);
    stack_destr(&stack_cpu.cpu);
    return 0;
}

// RESULT FILE
// RETURNED
// 0: WELL DONE
// 1: APPEAL TO EMPTY MEMORY CELL
//      (S) - STACK
//      (AX) - FIRST REGISTER
//      (BX) - SECOND REGISTER
// 2: ERROR IN BINARY OPERATION
// 3: UNKNOWN OPERATION
// 4: EXIT OUT OF PROGRAM
