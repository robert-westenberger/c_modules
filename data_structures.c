#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

/* DynamicArray */
DynamicArray *create_DynamicArray() {
    DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray));
    array->items= malloc(sizeof(int));
    array->size = 0;
    array->capacity=1;
    return array;
}

int size_DynamicArray(DynamicArray* array) {
    return array->size;
}

/* Todo: Am I doing this right..? Does this create any garbage or memory leaks?*/
bool enlarge_DynamicArray(DynamicArray* array) {
    int *items = realloc(array->items, sizeof(*(array->items)) * array->capacity * 2);
    if (items != NULL) {
        array->capacity = array->capacity * 2;
        array->items = items;
        return true;    
    }
    return false;
    
}
/* Inserts item into array at index, shifting others to the right if necessary.
Returns false is there is an error. */
bool addAtIndex_DynamicArray(DynamicArray* array, int item, int index) {
    // Check to see if we can add another item to the array..
    if (size_DynamicArray(array) + 1 > array->capacity) {
        if (!enlarge_DynamicArray(array)) {
            return false;
        }
    }
    array->size = array->size + 1;
    for (int i = size_DynamicArray(array) - 1; i > index; i--) {
        array->items[i] = array->items[i - 1];
    }
    array->items[index] = item;
    
    return true;
}
int getItemAtIndex_DynamicArray(DynamicArray* array, int index) {
    return array->items[index];
}
/* Removes item into array at index, shifting others to the right if necessary.
Returns false is there is an error. */
int removeAtIndex_DynamicArray(DynamicArray* array, int index) {
    int item = getItemAtIndex_DynamicArray(array, index);
    for (int i = index + 1; i < size_DynamicArray(array); i++) {
        array->items[i - 1] = array->items[i];
    }
    array->size--;
    return item;
}


/* Replaces item into array at index */
int replaceAtIndex_DynamicArray(DynamicArray* array, int item, int index) {
    int itemToBeReplaced = getItemAtIndex_DynamicArray(array, index);
    array->items[index] = item;
    return itemToBeReplaced;
}

bool append_DynamicArray(DynamicArray* array, int item) {
    return addAtIndex_DynamicArray(array, item, array->size);
}
bool prepend_DynamicArray(DynamicArray* array, int item) {
    return addAtIndex_DynamicArray(array, item, 0);
}

void forEach_DynamicArray(DynamicArray* array, void (*callback)(int item)) {
    for (size_t i = 0; i < array->size; i++) {
        callback(array->items[i]);
    }
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

/* The more "elegant" implementation of deletion from a linked list
suggested by linus torvalds. This removes separate branches to deal
with the special cases of deleting the first element, and the value
not being in the list at all.  */
void deleteFromListByValue2(List** list, int value) {
    Node **pointer_to_list_head = &(*list)->head;
    
    while (*pointer_to_list_head) { 
    if ((*pointer_to_list_head)->item == value) 
      *pointer_to_list_head = (*pointer_to_list_head)->next; 
    else 
      pointer_to_list_head = &((*pointer_to_list_head)->next);
  }
}