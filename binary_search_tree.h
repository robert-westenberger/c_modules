#include <stdbool.h>
#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_


typedef struct BSTNode {
    int item;
    struct BSTNode *parent;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;


/* Operations: Create, insert, search, delete, inorder traversal, preorder traversal
postorder traversal */
extern BSTNode* create_BinarySearchTree();
extern bool insert_BinarySearchTree(BSTNode **tree, int value);
extern void inOrderTraversal_BinarySearchTree(BSTNode* tree, void (*callback)(BSTNode node));
extern void preOrderTraversal_BinarySearchTree(BSTNode* tree, void (*callback)(BSTNode node));
extern void postOrderTraversal_BinarySearchTree(BSTNode* tree, void (*callback)(BSTNode node));
#endif