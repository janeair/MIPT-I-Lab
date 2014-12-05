#ifndef HASH_TABLE_C_INCLUDED
#define HASH_TABLE_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "double_linked_list.h"
#include "double_linked_list.c"
#include "hash_table.h"

hashtable_t* table_create (hashtable_t* table)
{
    table = (hashtable_t*)calloc(1,sizeof(hashtable_t));
    assert(table != 0);
    int i = 0;
    for (i = 0; i < tsize; i++)
        table->dlist[i] = list_create(table->dlist[i]);
    table->counter = 0;
    return table;
}

void table_push (hashtable_t* table, const char* data, int code)
{
    assert(table != 0);
    assert(data != 0);
    int hashcode = hashf(data);
    assert(hashcode >= 0 && hashcode < tsize);
    assert(table->dlist[hashcode] != 0);
    list_push(table->dlist[hashcode], data, code);
    table->counter++;
    return;
}

void table_pop (hashtable_t* table, const char* data)
{
    assert(table != 0);
    assert(data != 0);
    int hashcode = hashf(data);
    assert(hashcode >= 0 && hashcode < tsize);
    int error = list_pop(table->dlist[hashcode], data);
    if (error == 1)
        printf("- Sorry, this name not found -\n");
    else
        table->counter--;
    return;
}

void table_fpush (hashtable_t* table, const char* filepath)
{
    assert(table != 0);
    assert(filepath != 0);
    FILE* source;
    source = fopen(filepath, "r");
    assert(source != 0);
    while( !feof(source) )
    {
        char* name = (char*)calloc(30,sizeof(char));
        assert(name != 0);
        fscanf(source, "%s", name);
        table_push(table, name, 0);
        free(name);
    }
    fclose(source);
    return;
}

int table_search (hashtable_t* table, const char* data)
{
    assert(table != 0);
    assert(data != 0);
    int hashcode = hashf(data);
    assert(hashcode >= 0 && hashcode < tsize);
    return list_search(table->dlist[hashcode],data);
}

void name_search (hashtable_t* table, const char* data)
{
    assert(table != 0);
    assert(data != 0);
    int code = table_search(table, data);
    int hashcode = hashf(data);
    assert(hashcode >= 0 && hashcode < tsize);
    if (code != 0)
        printf("Name found!\n%s | %d | %d (hash)\n", data, code, hashcode);
    else
        printf("Name not found, sorry\n");
    return;
}

void table_hashprint(hashtable_t* table, int hashcode)
{
    assert(table != 0);
    if (hashcode >= 0 && hashcode < tsize)
        list_print(table->dlist[hashcode]);
    else
        printf("- Wrong Hash Code -\n");
    return;
}

void table_print(hashtable_t* table)
{
    assert(table != 0);
    int i = 0;
    printf("Table has %d records\n", table->counter);
    for (i = 0; i < tsize; i++)
        if (table->dlist[i]->ListSize > 0)
        {
            printf("hash -> %d\n", i);
            list_print(table->dlist[i]);
        }
    return;
}

void table_destroy (hashtable_t* table)
{
    assert(table != 0);
    int i = 0;
    for (i = 0; i < tsize; i++)
        list_destroy(table->dlist[i]);
    free(table);
    return;
}

int hashf (const char* data)
{
    assert(data != 0);
    int hashcode = 0;
    int i = 0;
    int len = strlen(data);
    for (i = 0; i < len; i++)
        hashcode += (int)data[i];
    return hashcode % tsize;
}

#endif // HASH_TABLE_C_INCLUDED
