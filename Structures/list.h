#ifndef _LIST_H_
#define _LIST_H_
#include <stdlib.h>

/*
 * /!\/!\ the list is strongly typed and only accept size_t for the first data
 * /!\/!\ and char* for the second data field.
 */

typedef struct linked_list
{
    size_t data1;
    char* data2;
    struct linked_list* next;
}linked_list;

//create a new list.
//return a pointer to the sentinel of the list.
linked_list* new_list();

//delete the list.
void delete_list(linked_list* list);

//insert the elements data1 and data2 at the end of the list.
void insert_list(linked_list* list, size_t data1, char* data2);

#endif
