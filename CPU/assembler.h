#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct label_t
{
    char* name;
    int point;
}
label_t;
// TYPE OF LABEL

// CODES OF COMMANDS (BELOW)
enum
{
    CPOP = 1,
    CPOPA = 2,
    CPOPB = 3,

    CPUSH = 10,
    CPUSHA = 11,
    CPUSHB = 12,
    CPUSHAX = 13,
    CPUSHBX = 14,

    CADD = 20,
    CMUL = 21,
    CSUB = 22,
    CDIV = 23,
    CSQR = 24,

    CMOVEAB = 30,
    CMOVEBA = 31,

    CLABEL = 0,
    CJMP = -1,
    CJE = -2,
    CJNE = -3,
    CJL = -4,
    CJNL = -5,
    CJG = -6,
    CJNG = -7,

    CCALL = -10,

    END = -50,

    ERROR = 404
};

label_t labels[100]; // ARRAY USING LABELS

int check_cmd (char* cmd)
// CHECKS COMMAND TYPE
{
    if ( strcmp(cmd,"POP") == 0) return CPOP;
    else if ( strcmp(cmd,"POPA") == 0) return CPOPA;
    else if ( strcmp(cmd,"POPB") == 0) return CPOPB;
    else if ( strcmp(cmd,"PUSH") == 0) return CPUSH;
    else if ( strcmp(cmd,"PUSHA") == 0) return CPUSHA;
    else if ( strcmp(cmd,"PUSHB") == 0) return CPUSHB;
    else if ( strcmp(cmd,"PUSHAX") == 0) return CPUSHAX;
    else if ( strcmp(cmd,"PUSHBX") == 0) return CPUSHBX;
    else if ( strcmp(cmd,"ADD") == 0) return CADD;
    else if ( strcmp(cmd,"MUL") == 0) return CMUL;
    else if ( strcmp(cmd,"SUB") == 0) return CSUB;
    else if ( strcmp(cmd,"DIV") == 0) return CDIV;
    else if ( strcmp(cmd,"SQR") == 0) return CSQR;
    else if ( strcmp(cmd,"MOVEAB") == 0) return CMOVEAB;
    else if ( strcmp(cmd,"MOVEBA") == 0) return CMOVEBA;
    else if ( strcmp(cmd,"JMP") == 0) return CJMP;
    else if ( strcmp(cmd,"JE") == 0) return CJE;
    else if ( strcmp(cmd,"JNE") == 0) return CJNE;
    else if ( strcmp(cmd,"JL") == 0) return CJL;
    else if ( strcmp(cmd,"JNL") == 0) return CJNL;
    else if ( strcmp(cmd,"JG") == 0) return CJG;
    else if ( strcmp(cmd,"JNG") == 0) return CJNG;
    else if ( strcmp(cmd,"CALL") == 0) return CCALL;
    else if ( strcmp(cmd,"END") == 0) return END;
    else if ( cmd[strlen(cmd)-1] == ':') return CLABEL;
    else return ERROR;
}

int find_label (const char* str, const int cur)
// FINDS LABEL AND RETURNS LABEL PATH (COMMAND NUMBER)
{
    assert(str != 0);
    int i;
    for (i=0; i<cur; i++)
        if ( strcmp(str, labels[i].name) == 0) return labels[i].point;
    return 0;
}

void assembler(const char* pathin, const char* pathout)
{
    // IN & OUT FILES

    FILE* source;
    FILE* output;

    char str[10]; // DECLARE WITH WHAT?
    int typecmd;
    int arg;

    // CURRENT COMMAND AND LABEL

    int cur_cmd=0;
    int cur_lbl=0;

    // FIRST STEP

    // CHEKING INPUT DATA

    assert(pathin != 0);
    assert(pathout != 0);

    source = fopen(pathin,"r");
    assert(source!=0);

    while( !feof(source) )
    {
        fscanf( source, "%s", str);
        int len = strlen(str)-1;
        if (str[len] == ':')
        {
            labels[cur_lbl].name = (char*)calloc(len+1,sizeof(char));
            assert(labels[cur_lbl].name != 0);
            strncpy(labels[cur_lbl].name, str, len);
            labels[cur_lbl].point = cur_cmd + 1;
            cur_lbl++;
        }
        else cur_cmd++;
    }

    // DEBUG INFORMATION

    int i;
    for (i = 0; i < cur_lbl; i++)
        printf("%d %s -> %d\n",i ,labels[i].name, labels[i].point);

     fclose(source);

    // SECOND STEP

    source = fopen(pathin,"r");
    output = fopen(pathout,"w");

    assert(source!=0);
    assert(output!=0);

    while ( !feof(source) )
    {

        fscanf( source, "%s", str);
        typecmd = check_cmd(str);
        if (typecmd != 0) fprintf( output, "%d ", typecmd);
        if (typecmd == CPUSH || typecmd == CPUSHAX || typecmd == CPUSHBX)
        {
            fscanf( source, "%d", &arg);
            fprintf( output, "%d", arg);
        }
        else if (typecmd == CJMP || typecmd == CJE || typecmd == CJNE || typecmd == CJL || typecmd == CJNL || typecmd == CJG || typecmd == CJNG)
                {
                    fscanf( source, "%s", str);
                    int cmd_go = find_label(str, cur_lbl);
                    if (cmd_go != 0)
                        fprintf( output, "%d", cmd_go);
                    else
                    {
                        printf("Wrong Format of Label or Label Not Found\n");
                        fprintf( output, "$0");
                    }
                }
        if (typecmd != 0) fprintf( output, "\n");
    }

    fclose(source);
    fclose(output);

    for (i = 0; i < cur_lbl; i++)
        free(labels[i].name);
}

#endif // ASSEMBLER_H_INCLUDED
