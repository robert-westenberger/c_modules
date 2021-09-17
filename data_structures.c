#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

/* Stack */
Stack* createStack(int maxsize) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->maxsize = maxsize;
    stack->top = -1;
    stack->items = (int*)malloc(stack->maxsize * sizeof(int));
    return stack; 
}

int isFullStack(Stack* stack)
{
    return stack->top == stack->maxsize - 1;
}

int isEmptyStack(Stack* stack)
{
    return stack->top == -1;
}

void push(Stack* stack, int item)
{
    if (isFullStack(stack))
        return;
    stack->items[++stack->top] = item;
    // printf("%d pushed to stack\n", item);
}

int pop(Stack* stack)
{
    if (isEmptyStack(stack))
        return INT_MIN;
    return stack->items[stack->top--];
}


/* List */
List *createList() {
    List *p = malloc(sizeof(List));
    p->head = NULL;
    return p;
}
/* Adds node to front of the list, making the newly added node the new
head */
void pushToList(List** list, int value) {
    Node *newNode;
    newNode = malloc(sizeof(Node));
    newNode->item = value;
    newNode->next = (*list)->head;
    (*list)->head = newNode;
}

// void printList(List* list)
// {
//     struct Node* ptr = list;
//     while (ptr)
//     {
//         printf("%d -> ", ptr->item);
//         ptr = ptr->next;
//     }
 
//     printf("NULL");
// }
// /* List */

// Node* createList() {
//     Node* list = NULL;
//     return list;
// }
// /* Recursive implementation of searching a linked list. If x is in the list,
// it is either the first element or located in the rest of the list. If 
// x is not in the list at all, eventually we search an empty list, which
// we know is the end (and x is not in the list) */
// Node *searchList(Node* list, int value) {
//     if (list == NULL){
//         return NULL;
//     }

//     if (list->item == value) {
//         return list;
//     }

//     return searchList(list->next, value);
// }

// void printList(Node* list) {
//     printf("%d, ", list->item);
//     if (list == NULL || list->next == NULL) {
//         return;
//     }
//     return printList(list->next);
// }


// /*
// Insert each new item in the beginning of the list so we don't have to 
// traverse it, and since we don't have need to maintain any particular order.
// We must update the pointer, here the parameter list, to the head of the data
// structure 
// */
// void insertIntoList(Node** list, int value) { 
//     Node* temporary_pointer;                    
//     temporary_pointer = malloc(sizeof(Node));
//     temporary_pointer->item = value;
//     temporary_pointer->next = *list;
//     *list = temporary_pointer;
// }

// /* Deletes the first node in the list that matches value. */
// void deleteFromListByValue(Node* head, int value) {
//     if (head == NULL){
//         return NULL;
//     }

//     if (head->item == value) {
//         return head;
//     }
// }

// /* Needed to find the predecessor of the node to be deleted, because
// it's next pointer needs to be updated */
// // Node* getPredecessor(Node* list, int value) {
// //     if ((list == NULL) || (list->next == NULL)) {
// //         return NULL;
// //     }
// //     if ((list->next->item) == value) {
// //         return list;
// //     } else {
// //         return(getPredecessor(list->next, value));
// //     }
// // }

// // void deleteFromList(Node** list, int value) {
// //     Node *temporaryPointer;
// //     Node *predecessorPointer;
// //     Node *currItemPointer;   

// //     temporaryPointer = *list;
// //     currItemPointer = searchList(*list, value);
// //     predecessorPointer = getPredecessor(*list, value);
    
// //     if (predecessorPointer == NULL) {
// //         *list = temporaryPointer->next;
// //     } else { // There exists a predecessor
// //         predecessorPointer->next = predecessorPointer->next;
// //     }
// //     free(predecessorPointer);

// // }