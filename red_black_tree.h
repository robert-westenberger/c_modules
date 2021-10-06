#include <stdbool.h>
#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

/* Red black trees are a kind of self-balancing binary search tree. Each node 
stores an extra bit representing "color" (red or black) that is used to ensure
that the tree remains balanced during insertions and deletions. */


typedef struct RBTNode {
    int item;
    enum {black, red} color; /* 0 black 1 red */
    struct RBTNode *parent;
    struct RBTNode *left;
    struct RBTNode *right;
} RBTNode;


/* Operations: Create, insert, search, delete, inorder traversal, preorder traversal
postorder traversal */
extern bool insert_RedBlackTree(RBTNode **tree, int value);
extern RBTNode* search_RedBlackTree(RBTNode *tree, int value);
extern RBTNode* minimum_RedBlackTree(RBTNode *tree);
extern RBTNode* maximum_RedBlackTree(RBTNode *tree);
extern RBTNode* deleteValue_RedBlackTree(RBTNode **root, int value);
extern int height_RedBlackTree(RBTNode *tree);
extern void print_RedBlackTree(RBTNode *tree, int row);
extern void inOrderTraversal_RedBlackTree(RBTNode *tree, void (*callback)(RBTNode node));
extern void preOrderTraversal_RedBlackTree(RBTNode *tree, void (*callback)(RBTNode node));
extern void postOrderTraversal_RedBlackTree(RBTNode *tree, void (*callback)(RBTNode node));

#endif