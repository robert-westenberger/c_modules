#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "red_black_tree.h"


static void rotateLeft_RedBlackTree(RBTNode **tree, RBTNode *node) {
    RBTNode *rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left != NULL) {
        rightChild->left->parent = node;
    }
    rightChild->parent = node->parent;
    if (node->parent == NULL) {
        *tree = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent = rightChild;
}
static void rotateRight_RedBlackTree(RBTNode **tree, RBTNode *node) {
    RBTNode *leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != NULL) {
        leftChild->right->parent = node;
    }
    leftChild->parent = node->parent;
    if (node->parent == NULL) {
        *tree = leftChild;
    } else if (node == node->parent->right) {
        node->parent->right = leftChild;
    } else {
        node->parent->left = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;
}
static void insertFixup_RedBlackTree(RBTNode **tree, RBTNode *newNode) {

    RBTNode *ancestorPointer = NULL; /* left or right of grandparent */
    int tempColor;
    /* iterate until newnode isnt the root, and newnodes parent isnt red */
    while (newNode != *tree && newNode->parent->color == red ) {
        
        /* Find ancestor ( aunt / uncle ) pointer */
        if (newNode->parent == newNode->parent->parent->left) {
            ancestorPointer = newNode->parent->parent->right;
        } 
        else {
            ancestorPointer = newNode->parent->parent->left;
        }

        /*
        2 cases depending on the color of the uncle: 
        if red, we do recolor
        if black, we do rotations and/or recoloring
        */
        /* check ancestor is not null.. if its null its color is black anyway */
        if (ancestorPointer != NULL && ancestorPointer->color == red) {
            newNode->parent->color = black;
            ancestorPointer->color = black;
            newNode->parent->parent->color = red;
            newNode = newNode->parent->parent;
        }
        else { /* aunt/uncle node is black (or its null, 
                    which we also treat as black) */

            /* Nodes uncle is black, we have 4 cases */
            /* Left Left Rotation 
            (i)  Swap color of parent and grandparent
            (ii) Right Rotate Grandparent
            */
            if (newNode->parent->parent != NULL && 
            newNode->parent == newNode->parent->parent->left && 
            newNode == newNode->parent->left) {
                tempColor = newNode->parent->color;
                newNode->parent->color = newNode->parent->parent->color;
                newNode->parent->parent->color = tempColor;
                rotateRight_RedBlackTree(tree, newNode->parent->parent);
            }
            /*
            Left-Right (LR) case, do following
            (i)  Swap color of current node  and grandparent
            (ii) Left Rotate Parent
            (iii) Right Rotate Grand Parent
            */
            if (newNode->parent->parent != NULL && 
            newNode->parent == newNode->parent->parent->left && 
            newNode == newNode->parent->right) {
                tempColor = newNode->color;
                newNode->color = newNode->parent->parent->color;
                newNode->parent->parent->color = tempColor;
                rotateLeft_RedBlackTree(tree, newNode->parent);
                rotateRight_RedBlackTree(tree, newNode->parent->parent);
            }
            /*
            Right-Right (RR) case, do following
            (i)  Swap color of parent and grandparent
            (ii) Left Rotate Grandparent
            */
            if (newNode->parent->parent != NULL &&
                newNode->parent == newNode->parent->parent->right && 
                newNode == newNode->parent->right) {
                tempColor = newNode->parent->color;
                newNode->parent->color = newNode->parent->parent->color;
                newNode->parent->parent->color = tempColor;
                rotateLeft_RedBlackTree(tree, newNode->parent->parent);
            }
            /*
            Right-Left (RL) case, do following
            (i)  Swap color of current node  and grandparent
            (ii) Right Rotate Parentvvgl
            (iii) Left Rotate Grand Parent
            */
            if (newNode->parent->parent != NULL &&
            newNode->parent == newNode->parent->parent->right && 
            newNode == newNode->parent->left) {
                tempColor = newNode->parent->color;
                newNode->color = newNode->parent->parent->color;
                newNode->parent->parent->color = tempColor;
                rotateRight_RedBlackTree(tree, newNode->parent);
                rotateLeft_RedBlackTree(tree, newNode->parent->parent);
            }
        }
       
    }
    
    (*tree)->color = black;
}

bool insert_RedBlackTree(RBTNode **tree, int value) {
   RBTNode *treePtr = *tree;
   RBTNode *newNode =  malloc(sizeof(RBTNode));
   RBTNode *newNodeParent = NULL;

   newNode->item = value;
   newNode->left = NULL;
   newNode->right = NULL;
   newNode->parent = NULL;
   newNode->color = red; 
   while (treePtr != NULL) {
        newNodeParent = treePtr;
        if ((treePtr)->item > value) {
            treePtr = treePtr->left;
        } else {
            treePtr = treePtr->right;
        }
    }
    newNode->parent = newNodeParent;
    if (newNodeParent == NULL) {
        newNode->color = black;
        *tree = newNode;
    } 
    else if(newNodeParent->item > value) {
        newNodeParent->left = newNode;
    } else {
        newNodeParent->right = newNode;
    }
    insertFixup_RedBlackTree(tree, newNode);
    return true;
}

void print_RedBlackTree(RBTNode *tree, int row) {
    if (tree == NULL) {
        return;
    }

    print_RedBlackTree(tree->right, row+2);

    printf("\n ");
    for (int i = 0 ; i < row; i ++) { 
        printf(" ");
    }
    printf("%d", tree->item);
    print_RedBlackTree(tree->left, row+2);
}