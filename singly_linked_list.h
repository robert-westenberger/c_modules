#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H


typedef struct Node
{
    void *key;
    void *val;
    struct Node *next;
} Node;

/* NodeKeyOps and NodeValOps are traits that allow users to 
specify how the hash is computed, how its copied and how memory is managed. */
typedef struct NodeKeyOps
{
    void *(*cp)(const void *data, void *arg);
    void (*free)(void *data, void *arg);
    bool (*eq)(const void *data1, const void *data2, void *arg);
    void *arg;
} NodeKeyOps;

typedef struct NodeValOps
{
    void *(*cp)(const void *data, void *arg);
    void (*free)(void *data, void *arg);
    bool (*eq)(const void *data1, const void *data2, void *arg);
    void *arg;
} NodeValOps;

typedef struct SinglyLinkedList
{
    size_t capacity; /* total number of available buckets */
    size_t size;     /* The total number of elements */
    Node **buckets;
    NodeKeyOps key_ops;
    NodeValOps val_ops;
} SinglyLinkedList;

extern SinglyLinkedList *create_SinglyLinkedList(NodeKeyOps key_ops, NodeValOps val_ops);
extern void free_SinglyLinkedList(SinglyLinkedList *list);
extern void *get_SinglyLinkedList(SinglyLinkedList *list, const void *key);
extern bool contains_SinglyLinkedList(SinglyLinkedList *list, const void *key);
extern void put_SinglyLinkedList(SinglyLinkedList *list, const void *key, const void *val);
extern void print_SinglyLinkedList(SinglyLinkedList *list, void (*print_key)(const void *key), void (*print_val)(const void *val));


/* String Operations */

void *string_cp(const void *data, void *arg);
bool string_eq(const void *data1, const void *data2, void *arg);
void string_free(void *data, void *arg);
void string_print(const void *data);

extern NodeKeyOps key_ops_string;
extern NodeValOps val_ops_string;
#endif