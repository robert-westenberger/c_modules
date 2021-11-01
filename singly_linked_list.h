#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H


typedef struct Node
{
    void *data;
    struct Node *next;
} Node;


typedef struct NodeDataOps
{
    void *(*cp)(const void *data);
    void (*free)(void *data);
    bool (*eq)(const void *data1, const void *data2);
} NodeDataOps;

typedef struct SinglyLinkedList
{   
    int size;
    struct Node *head;
    NodeDataOps data_ops;
} SinglyLinkedList;

extern SinglyLinkedList *create_SinglyLinkedList(NodeDataOps data_ops);
extern void free_SinglyLinkedList(SinglyLinkedList *list);
extern int sizeof_SinglyLinkedList(SinglyLinkedList *list);
extern bool contains_SinglyLinkedList(SinglyLinkedList *list, const void *data);
extern void insert_SinglyLinkedList(SinglyLinkedList *list, const void *data);
extern void deleteValue_SinglyLinkedList(SinglyLinkedList *list, const void *data);
extern void print_SinglyLinkedList(SinglyLinkedList *list, void (*print_data)(const void *data));

/* String Operations */

void *string_cp(const void *data);
bool string_eq(const void *data1, const void *data2);
void string_free(void *data);
void string_print(const void *data);

extern NodeDataOps data_ops_string;
#endif