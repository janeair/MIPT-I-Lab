#include <stdio.h>
#include <string.h>
#include <assert.h>

// type of label

typedef struct label_t
{
    char* name;
    int point;
}
label_t;

// array of using labels
label_t labels[10];

// check type of command

int check_cmd (char* cmd)
{
    if ( strcmp(cmd,"pop") == 0) return 1;
    else if ( strcmp(cmd,"popa") == 0) return 2;
    else if ( strcmp(cmd,"popb") == 0) return 3;
    else if ( strcmp(cmd,"push") == 0) return 10;
    else if ( strcmp(cmd,"pusha") == 0) return 11;
    else if ( strcmp(cmd,"pushb") == 0) return 12;
    else if ( strcmp(cmd,"pushax") == 0) return 13;
    else if ( strcmp(cmd,"pushbx") == 0) return 14;
    else if ( strcmp(cmd,"add") == 0) return 20;
    else if ( strcmp(cmd,"mul") == 0) return 21;
    else if ( strcmp(cmd,"sub") == 0) return 22;
    else if ( strcmp(cmd,"div") == 0) return 23;
    else if ( strcmp(cmd,"jump") == 0) return -1;
    else if ( cmd[strlen(cmd)-1] == ':') return 0;
    else return 404;
}

int find_label (const char* str, const int cur)
{
    int i;
    for (i=0; i<cur; i++)
        if ( strcmp(str, labels[i].name) == 0) return labels[i].point;
    return 0;
}

int main()
{
    // IN & OUT files
    FILE* source;
    FILE* output;
    //
    char str[10];
    int tpcmd;
    int arg;
    // current command and label
    int cur_cmd=0;
    int cur_lbl=0;
    // path to IN & OUT files (and COMMANDLIST file)
    //const char *pathcmd = "D:/Олег/Проекты/ILab/newcmd.txt";
    const char *pathin = "D:/Олег/Проекты/ILab/source.txt";
    const char *pathout = "D:/Олег/Проекты/ILab/output.txt";

    // FIRST STEP

    source = fopen(pathin,"r");
    assert(source!=0);

    while( !feof(source) )
    {
        fscanf( source, "%s", str);
        int len = strlen(str)-1;
        if (str[len]==':')
        {
            labels[cur_lbl].name = (char*)calloc(len+1,sizeof(char));
            strncpy(labels[cur_lbl].name, str, len);
            labels[cur_lbl].point = cur_cmd + 1;
            cur_lbl++;
        }
        else cur_cmd++;
    }
    // counter
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
        tpcmd = check_cmd(str);
        if (tpcmd != 0) fprintf( output, "%d ", tpcmd);
        if (tpcmd/10 == 1)
        {
            fscanf( source, "%d ", &arg);
            fprintf( output, "%d ", arg);
        }
        else if (tpcmd == -1)
                {
                    fscanf( source, "%s", str);
                    int cmd_go = find_label(str, cur_lbl);
                    if (cmd_go != 0)
                        fprintf( output, "%d ", cmd_go);
                    else {
                        printf("Wrong Format of Label or Label Not Found");
                        fprintf( output, "$0 "); }
                }
    }

    fclose(source);
    fclose(output);

    return 0;
}
