#include <stdio.h>
#include <string.h>
#include <assert.h>

int check_cmd (char* cmd)
{
    if ( strcmp(cmd,"push") == 0) return 0;
    else if ( strcmp(cmd,"pop") == 0) return 1;
    else if ( strcmp(cmd,"add") == 0) return 2;
    else if ( strcmp(cmd,"mul") == 0) return 3;
    else if ( strcmp(cmd,"sub") == 0) return 4;
    else if ( strcmp(cmd,"div") == 0) return 5;
    else if ( strcmp(cmd,"pusha") == 0) return 6;
    else if ( strcmp(cmd,"pushb") == 0) return 7;
    else if ( strcmp(cmd,"popa") == 0) return 8;
    else if ( strcmp(cmd,"popb") == 0) return 9;
    else if ( strcmp(cmd,"pushax") == 0) return 10;
    else if ( strcmp(cmd,"pushbx") == 0) return 11;
}

int main()
{
    FILE* source;
    FILE* output;
    char str[10];
    int tpcmd;
    int arg;
    char *pathin = "C:/Users/User/Desktop/source.txt";
    char *pathout = "C:/Users/User/Desktop/output.txt";

    source = fopen(pathin,"r");
    output = fopen(pathout,"w");

    assert(source!=0);
    assert(output!=0);
    while ( !feof(source) )
    {

        fscanf( source, "%s", str);
        tpcmd = check_cmd(str);
        fprintf( output, "%d ", tpcmd);
        if (tpcmd == 0 || tpcmd == 10 || tpcmd == 11 )
        {
            fscanf( source, "%d ", &arg);
            fprintf( output, "%d ", arg);
        }
    }
    fclose(source);
    fclose(output);
    return 0;
}
