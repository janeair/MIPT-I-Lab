#ifndef HASH_TABLE_H_INCLUDED
#define HASH_TABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "double_linked_list.h"

typedef struct hashtable_t
{
    dlist_t* dlist[100];
    long counter;
}
hashtable_t;
// STRUCT OF HASH TABLE THE SIZE 100

hashtable_t* table_create (hashtable_t* table);
// CREATES EMPTY HASH TABLE

void table_fpush (hashtable_t* table, const char* filepath);
// FILLS THE TABLE WITH RECORDS (NAME = WORD | CODE = 0) FROM THE FILE "FILEPATH"

void table_push (hashtable_t* table, const char* data, int code);
// PUSHES NEW RECORD (NAME + SOURCE) IN THE HASH TABLE ACCORDING TO ITS HASH

void table_pop (hashtable_t* table, const char* data);
// DELETES RECORD WITH NAME "DATA" FROM THE TABLE

int table_search (hashtable_t* table, const char* data);
// CHECKS WHETHER THE HASH TABLE HAS THIS NAME
// RETURNS:
// SOURCE (INT) IF THE NAME WAS FOUND
// 0 IF NOT

void name_search (hashtable_t* table, const char* data);
// CHECKS WHETHER THE HASH TABLE HAS THIS NAME
// PRINTS:
// RECORD (NAME | SOURCE | HASH) IF THE NAME WAS FOUND
// "NAME NOT FOUND" IF NOT

int hashf (const char* data);
// HASH FUNCTION
// HASH = MOD OF SUM ASCII-CODES OF SYMBOLS FROM DIVISION BY 100
// RETURNS HASH CODE (0 TO 99)

void table_hashprint(hashtable_t* table, int hashcode);
// PRINTS LIST FROM THE TABLE ACCORDING TO HASHCODE

void table_print(hashtable_t* table);
// PRINTS HASH TABLE AT ALL
// FORMAT : HASH -> "HASHCODE"
//          ELEMENTS (BELOW)

void table_destroy (hashtable_t* table);
// DESTROYS HASH TABLE AT ALL

#endif // HASH_TABLE_H_INCLUDED
