#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_search_tree.h"

bool insert_BinarySearchTree(BSTNode **tree, int value) {
    BSTNode *currNode = NULL;
    BSTNode *treePtr = *tree;
    BSTNode *newNode =  malloc(sizeof(BSTNode));
    newNode->item = value;
    newNode->left = NULL;
    newNode->right = NULL;


    while (treePtr != NULL) {
        currNode = treePtr;
        if ((treePtr)->item > value) {
            treePtr = (treePtr)->left;
        } else {
            treePtr = (treePtr)->right;
        }
    }
    newNode->parent = currNode;
    if (currNode == NULL) {
        *tree = newNode;
    } else {
        if (currNode->item > value) {
            currNode->left = newNode;
        } else {
            currNode->right = newNode;
        }
    }
    
    return true;
}
// printf("%d %d %p %p \n", value, (*tree)->item, (*tree)->left, (*tree)->right);
// DoublyLinkedNode *newNode;
//     newNode = malloc(sizeof(DoublyLinkedNode));
//     newNode->item = value;
//     newNode->next = (*list)->head;
//     newNode->prev = NULL;

//     if (isEmpty_DoublyLinkedList(*list)) {
//         (*list)->tail = newNode;
//     }
//     (*list)->head = newNode; 