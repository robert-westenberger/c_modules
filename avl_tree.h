#include <stdbool.h>
#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef struct AVLNode
{
    void *data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

typedef struct AVLNodeDataOps
{
    void *(*cp)(const void *data);
    void (*free)(void *data);
    bool (*eq)(const void *data1, const void *data2);
    int (*compare)(const void *data1, const void *data2);
    void (*print)(const void *data);
} AVLNodeDataOps;

typedef struct AVLTree
{
    struct AVLNode *head;
    AVLNodeDataOps data_ops;
} AVLTree;


extern AVLTree *create_AVLTree(AVLNodeDataOps data_ops);
extern bool contains_AVLTree(AVLTree *tree, const void *data);
extern AVLNode *insert_AVLTree(AVLTree *tree, AVLNode *node, const void *data);
extern void deleteValue_AVLTree(AVLTree *tree, const void *data);

void *string_cp(const void *data);
bool string_eq(const void *data1, const void *data2);
int string_compare(const void *data1, const void *data2);
void string_free(void *data);
void string_print(const void *data);

void *int_cp(const void *data);
bool int_eq(const void *data1, const void *data2);
int int_compare(const void *data1, const void *data2);
void int_free(void *data);
void int_print(const void *data);

extern AVLNodeDataOps data_ops_string;
extern AVLNodeDataOps data_ops_int;

#endif