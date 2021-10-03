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


BSTNode* search_BinarySearchTree(BSTNode *tree, int value) {
    if (tree == NULL) {
        return NULL;
    }
    if (tree->item == value) {
        return tree;
    }
    if (value < tree->item) {
        return search_BinarySearchTree(tree->left, value);
    }
    return search_BinarySearchTree(tree->right, value);
}

BSTNode* minimum_BinarySearchTree(BSTNode *tree){
    BSTNode* minimum;
    if (tree == NULL) {
        return NULL;
    }
    minimum = tree;
    while (minimum->left != NULL) {
        minimum = minimum->left;
    }
    return minimum;
}
BSTNode* maximum_BinarySearchTree(BSTNode *tree){
    BSTNode* maximum;
    if (tree == NULL) {
        return NULL;
    }
    maximum = tree;
    while (maximum->right != NULL) {
        maximum = maximum->right;
    }
    return maximum;
}
/* Returns the node that was deleted */
BSTNode* deleteValue_BinarySearchTree(BSTNode *tree, int value) {
    if (tree == NULL) {
        return tree;
    }
    if (value < tree->item) {
        tree->left = deleteValue_BinarySearchTree(tree->left, value);
    } 
    else if (value > tree->item) {
        tree->right = deleteValue_BinarySearchTree(tree->right, value);
    }
    else {
        if (tree->left == NULL) {
            BSTNode* temp = tree->left;
            free(tree);
            return temp;
        }
        else if (tree->right == NULL) {
            BSTNode* temp = tree->right;
            free(tree);
            return temp; 
        }
        BSTNode* temp = minimum_BinarySearchTree(tree->right);
        tree->item = temp->item;
        tree->right = deleteValue_BinarySearchTree(tree->right, temp->item);
    }
    return tree;
}
static int heightIter_BinarySearchTree(BSTNode *tree, int currentHeight, int maxHeight) {
    if (tree == NULL) {
        return maxHeight;
    }
    currentHeight++;
    if (currentHeight > maxHeight) {
        return heightIter_BinarySearchTree(tree->left, currentHeight, currentHeight),  
        heightIter_BinarySearchTree(tree->right, currentHeight, currentHeight);
    } else {
        return heightIter_BinarySearchTree(tree->left, currentHeight, maxHeight), 
        heightIter_BinarySearchTree(tree->right, currentHeight, maxHeight);
    }
    return maxHeight;
}
int height_BinarySearchTree(BSTNode *tree) {
    return heightIter_BinarySearchTree(tree, 0, 0);
}
void print_BinarySearchTree(BSTNode *tree, int row) {
    if (tree == NULL) {
        return;
    }

    print_BinarySearchTree(tree->right, row+2);

    printf("\n ");
    for (int i = 0 ; i < row; i ++) { 
        printf(" ");
    }
    printf("%d", tree->item);
    print_BinarySearchTree(tree->left, row+2);
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