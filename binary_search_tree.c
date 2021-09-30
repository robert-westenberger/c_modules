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



void inOrderTraversal_BinarySearchTree(BSTNode* tree, void (*callback)(BSTNode node)) {
    if (tree != NULL) {
        inOrderTraversal_BinarySearchTree(tree->left, callback);
        callback(*tree);
        inOrderTraversal_BinarySearchTree(tree->right, callback);
    }
}
void preOrderTraversal_BinarySearchTree(BSTNode* tree, void (*callback)(BSTNode node)) {
    if (tree != NULL) {
        callback(*tree);
        preOrderTraversal_BinarySearchTree(tree->left, callback);
        preOrderTraversal_BinarySearchTree(tree->right, callback);
    }
}
void postOrderTraversal_BinarySearchTree(BSTNode* tree, void (*callback)(BSTNode node)) {
    if (tree != NULL) {
        postOrderTraversal_BinarySearchTree(tree->left, callback);
        postOrderTraversal_BinarySearchTree(tree->right, callback);
        callback(*tree);
    }
}