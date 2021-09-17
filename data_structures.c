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

void printList(List* list)
{
    struct Node* ptr = list->head;
    while (ptr)
    {
        printf("%d -> ", ptr->item);
        ptr = ptr->next;
    }
    printf("END OF LIST");
}
/* Straightforward but inelegant, containing a lot of conditionals
to check for special cases*/
void deleteFromListByValue(List** list, int value) {
    Node *temp = (*list)->head, *prev;

    /* head contains item to be deleted */
    if (temp != NULL && temp->item == value) { 
        (*list)->head = temp->next;
        free(temp);
        return;
    }

    /* Search the list for the value to be deleted, 
    keeping track of the previous node as it needs to be 
    updated. */
    while (temp != NULL && temp->item != value) { 
        prev = temp; 
        temp = temp->next; 
    }

    /* Value was not in linked list */
    if (temp == NULL) {
        return; 
    }
       
     prev->next = temp->next; 
     free(temp); // Free memory 
}
