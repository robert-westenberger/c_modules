#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "red_black_tree.h"

/* TODO: NOT DONE. DELETE FIXUP IS INCOMPLETE */ 
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

RBTNode* minimum_RedBlackTree(RBTNode *tree){
    RBTNode* minimum;
    if (tree == NULL) {
        return NULL;
    }
    minimum = tree;
    while (minimum->left != NULL) {
        minimum = minimum->left;
    }
    return minimum;
}

/* replaces one subtree as a child of its parent with
another subtree */
static void transplant_RedBlackTree(RBTNode **tree, RBTNode *node1, RBTNode *node2) {
    if (node1->parent == NULL) {
        *tree = node2;
    }
    else if (node1 == node1->parent->left) {
        node1->parent->left = node2;
    }
    else {
        node1->parent->right = node2;
    }
    if (node2 != NULL) {
        node2->parent = node1->parent;
    }
    
}

void deleteValueFixup_RedBlackTree(RBTNode **root, RBTNode *x) {
    RBTNode* tree = *root;
    RBTNode* sibling;
    __asm("nop");
    while (x != tree) {
        if (x == x->parent->left) {
            sibling = x->parent->right;
            if (sibling->color == red) { // case 1
                sibling->color = black;
                x->parent->color = red;
                rotateLeft_RedBlackTree(root, x->parent);
                sibling = x->parent->right;
            }
            if ((sibling->right == NULL || sibling->right->color == black) && (sibling->left == NULL || sibling->left->color == black)) { // case 2
                sibling->color = red;
                x = x->parent;
            } else if (sibling->right == NULL || sibling->right->color == black) { // case 3
                sibling->left->color = black;
                sibling->color = red;
                rotateRight_RedBlackTree(root, sibling);
                sibling = x->parent->right;
            }
            else { // case 4
                sibling->color = x->parent->color;
                x->parent->parent->color = black;
                sibling->right->color = black;
                rotateLeft_RedBlackTree(root, x->parent);
                x = *root;
            }
        }
        else {
            sibling = x->parent->left;
            if (sibling->color == red) { // case 1
                sibling->color = black;
                x->parent->color = red;
                rotateRight_RedBlackTree(root, x->parent);
                sibling = x->parent->left;
            }
            if ((sibling->right == NULL || sibling->right->color == black) && (sibling->left == NULL || sibling->left->color == black)) { // case 2
                sibling->color = red;
                x = x->parent;
            } else if (sibling->left == NULL || sibling->left->color == black) { // case 3
                sibling->right->color = black;
                sibling->color = red;
                rotateLeft_RedBlackTree(root, sibling);
                sibling = x->parent->right;
            }
            else { // case 4
                sibling->color = x->parent->color;
                x->parent->parent->color = black;
                sibling->left->color = black;
                rotateRight_RedBlackTree(root, x->parent);
                x = *root;
            }
        }
        x->color = black;
    }
}
RBTNode* deleteValue_RedBlackTree(RBTNode **root, int value) {
    RBTNode* tree = *root;
    RBTNode* deletedNode;
    RBTNode* x; /* This node moves into y's original position in the tree.
                    This node might cause violations of the red-black properties. */ 
    RBTNode* y; /* Need to keep track of this node that might violate */
                    /* red black properties */
    int originalColor;
    while (tree) {
        if (value < tree->item) {
            tree = tree->left;
        }
        else if (value > tree->item) {
            tree = tree->right;
        }
        else {
            break;
        }
    }
    
    deletedNode = tree;
    /* The node we are deleting has fewer than two children. */
    if (deletedNode->left == NULL || deletedNode->right == NULL) {
        y = deletedNode;
        originalColor = y->color;
        if (deletedNode->left == NULL) {
            x = deletedNode->right;
            transplant_RedBlackTree(root, deletedNode, x);
        } else {
            x = deletedNode->left;
            transplant_RedBlackTree(root, deletedNode, x);
        }

    } else { /* The node we are deleting has two children. */
        y = minimum_RedBlackTree(tree->right);
        originalColor = y->color;
        x = y->right;
        if (y->parent == deletedNode) {
            x->parent = y;
        } else {
            transplant_RedBlackTree(root, y, x);
        }
        transplant_RedBlackTree(root, deletedNode, y);
        y->color = originalColor;
    }
    if (originalColor == black) {
        deleteValueFixup_RedBlackTree(root, x);
    }
    return *root;  
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