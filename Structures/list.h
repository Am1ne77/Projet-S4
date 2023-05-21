#ifndef _LIST_H_
#define _LIST_H_
#include <stdlib.h>

typedef struct linked_list
{
    size_t data1;
    char* data2;
    struct linked_list* next;
}linked_list;

linked_list* new_list();

void delete_list(linked_list* list);

void insert_list(linked_list* list, size_t data1, char* data2);
#endif
