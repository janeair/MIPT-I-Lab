#ifndef DOUBLE_LINKED_LIST_H_INCLUDED
#define DOUBLE_LINKED_LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct unit
{
    char* name;
    int source;
    struct unit* next;
    struct unit* prev;
}
unit;
// STRUCT OF LIST ELEMENT
// SOURCE - PEACE OF INFORMATION (FOR EX, PHONE NUMBER)

typedef struct dlist_t
{
    unit* head;
    int ListSize;
}
dlist_t;
// STRUCT OF DOUBLE LINKED LIST
// HEAD POINTS ON FIRST ELEMENT OF LIST

dlist_t* list_create(dlist_t* dlist);
// CREATES EMPTY LIST

void list_change(unit* unit1, unit* unit2);
// ! PRIVATE METHOD ! (PARENT -> LIST_SORT)
// EXCHANGES THE VALUES OF TWO ELEMENTS

void list_sort(dlist_t* dlist);
// SORTS LIST IN ASCENDING ORDER OF NAMES

void list_push(dlist_t* dlist, const char* data, int code);
// PUSHES NEW RECORD (NAME + SOURCE) IN THE LIST

int list_pop (dlist_t* dlist, const char* data);
// DELETES RECORD WITH NAME "DATA" FROM THE LIST
// RETURNS:
// 0 : EVERYTHING IS OK
// 1 : NAME NOT FOUND

int list_search(dlist_t* dlist, const char* data);
// CHECKS WHETHER THE LIST HAS THIS NAME
// RETURNS:
// SOURCE (INT) IF THE NAME WAS FOUND
// 0 IF NOT

void list_print (dlist_t* dlist);
// PRINTS LIST STARTING FROM HEAD

void list_destroy(dlist_t* dlist);
// DESTROYS LIST AT ALL

#endif // DOUBLE_LINKED_LIST_H_INCLUDED
