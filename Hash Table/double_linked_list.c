#ifndef DOUBLE_LINKED_LIST_C_INCLUDED
#define DOUBLE_LINKED_LIST_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "double_linked_list.h"

dlist_t* list_create(dlist_t* dlist)
{
    dlist = (dlist_t*)calloc(1,sizeof(dlist_t));
    assert(dlist!=0);
    dlist->head = NULL;
    dlist->ListSize = 0;
    return dlist;
}

void list_change(unit* unit1, unit* unit2)
{
    unit* temp = (unit*)calloc(1,sizeof(unit));
    assert(temp!=0);
    temp->name = (char*)calloc(30,sizeof(char)); // ! NAME MIGHT HAVE ONLY 30 SYMBOLS AT ALL !
    assert(temp->name!=0);

    strcpy(temp->name,unit1->name);
    temp->source = unit1->source;
    strcpy(unit1->name,unit2->name);
    unit1->source = unit2->source;
    strcpy(unit2->name,temp->name);
    unit2->source = temp->source;

    free(temp->name);
    free(temp);
    return;
}

void list_sort(dlist_t* dlist)
{
    assert(dlist!=0);
    unit* current = dlist->head;
    assert(current!=0);

    while (current->next!=0 && strcmp(current->name,current->next->name)>0)
    {
            list_change(current,current->next);
            current = current->next;
    }
    return;
}

void list_push(dlist_t* dlist, const char* data, int code)
{
    assert(dlist!=0);
    unit* record = (unit*)calloc(1,sizeof(unit));
    assert(record!=0);
    record->name = (char*)calloc(20,sizeof(char));
    assert(record->name!=0);

    strcpy(record->name, data);
    record->source = code;
    record->prev = NULL;
    if (dlist->head == 0)
    {
        record->next = NULL;
        dlist->head = record;
    }
    else
    {
        record->next = dlist->head;
        dlist->head = record;
        list_sort(dlist);
    }
    dlist->ListSize++;
    return;
}

void list_print (dlist_t* dlist)
{
    assert(dlist!=0);
    unit* current = dlist->head;
    do
    {
        printf("%s | %d\n",current->name,current->source);
        current = current->next;
    }
    while (current!=0);
    return;
}

int list_search(dlist_t* dlist, const char* data)
{
    assert(dlist!=0);
    unit* current = dlist->head;
    do
    {
        if (strcmp(current->name, data) == 0) return current->source;
        current = current->next;
    }
    while (current!=0);
    return 0;
}

void list_destroy(dlist_t* dlist)
{
    assert(dlist!=0);
    while (dlist->head->next!=0)
    {
        unit* temp = dlist->head;
        dlist->head = dlist->head->next;
        free(temp->name);
        free(temp);
    }
    free(dlist->head);
    free(dlist);
    return;
}

#endif // DOUBLE_LINKED_LIST_C_INCLUDED
