#include <stdlib.h>
#include "list.h"

linked_list* new_list()
{
    linked_list* list = malloc(sizeof(linked_list));
    list->data1 = NULL;
    list->data2 = NULL;
    list->next = NULL;

    return list;
}

void delete_list(linked_list* list)
{
    struct linked_list* current = list->next;
    while (current != NULL) {
        struct linked_list* next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

void insert_list(linked_list* list, size_t data1, char* data2)
{
    struct linked_list* to_insert = malloc(sizeof(linked_list));
    to_insert->data1 = data1;
    to_insert->data2 = data2;
    to_insert->next = NULL;

    struct linked_list* p = list;
    while(p->next != NULL)
        p = p->next;

    p->next = to_insert;
}
