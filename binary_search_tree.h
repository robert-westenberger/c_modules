#include <stdbool.h>
#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_


typedef struct BSTNode {
    int item;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;


/* Operations: Create, insert, search, delete, inorder traversal, preorder traversal
postorder traversal */
extern bool insert_BinarySearchTree(BSTNode **tree, int value);
extern bool insertRecursive_BinarySearchTree(BSTNode **tree, int value);
extern BSTNode* search_BinarySearchTree(BSTNode *tree, int value);
extern BSTNode* minimum_BinarySearchTree(BSTNode *tree);
extern BSTNode* maximum_BinarySearchTree(BSTNode *tree);
extern BSTNode* deleteValue_BinarySearchTree(BSTNode *tree, int value);
extern int height_BinarySearchTree(BSTNode *tree);
extern void print_BinarySearchTree(BSTNode *tree, int row);
extern void inOrderTraversal_BinarySearchTree(BSTNode *tree, void (*callback)(BSTNode node));
extern void preOrderTraversal_BinarySearchTree(BSTNode *tree, void (*callback)(BSTNode node));
extern void postOrderTraversal_BinarySearchTree(BSTNode *tree, void (*callback)(BSTNode node));
#endif