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

/* creates and returns a pointer to a new dynamic array
of size 0. If there is no more memory, returns NULL. */
DynamicArray *create_DynamicArray() {
    DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray));
    array->items= malloc(sizeof(int));
    array->size = 0;
    array->capacity=1;
    return array;
}
/* Returns size of the dynamic array */
int size_DynamicArray(DynamicArray* array) {
    return array->size;
}

/* Todo: Am I doing this right..? Does this create any garbage or memory leaks?*/
/* Increases capacity of the dynamic array, returning false if there is an
error. Just for simplicity the capacity is doubled each time. */
bool enlarge_DynamicArray(DynamicArray* array) {
    int *items = realloc(array->items, sizeof(*(array->items)) * array->capacity * 2);
    if (items != NULL) {
        array->capacity = array->capacity * 2;
        array->items = items;
        return true;    
    }
    return false;  
}
/* Shrinks capacity of the dynamic array, cutting it by half whenever
the size falls below 1/2 capacity */
bool shrink_DynamicArray(DynamicArray* array) {
    int *items = realloc(array->items, sizeof(*(array->items)));
    if (items != NULL) {
        array->capacity = array->capacity / 2;
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
/* Gets and returns item at position index. Doesnt check if its a valid
index or anything, so behavior will be undefined if given a bad index. */
int getItemAtIndex_DynamicArray(DynamicArray* array, int index) {
    return array->items[index];
}
/* Removes item from array at index, shifting others to the left if necessary,
and returns the item. 
*/
int removeAtIndex_DynamicArray(DynamicArray* array, int index) {
    int item = getItemAtIndex_DynamicArray(array, index);
    for (int i = index + 1; i < size_DynamicArray(array); i++) {
        array->items[i - 1] = array->items[i];
    }
    array->size--;
    return item;
}
/* Removes item from array at index, shifting others to the left if necessary,
and returns the item. The internal static array will be cut in half
whenever size is below 1/2 of the capacity. 
*/
int removeAtIndex2_DynamicArray(DynamicArray* array, int index) {
    if (size_DynamicArray(array) - 1 < (array->capacity) / 2) {
        if (!shrink_DynamicArray(array)) {
            return false;
        }
    }
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
/* Inserts item into array at the end. Returns false if error. */
bool append_DynamicArray(DynamicArray* array, int item) {
    return addAtIndex_DynamicArray(array, item, array->size);
}
/* Inserts item into array at the beginning, shifting everything else 
1 index to the right. Returns false if error. */
bool prepend_DynamicArray(DynamicArray* array, int item) {
    return addAtIndex_DynamicArray(array, item, 0);
}
/* Executes callback for each element in the array. */
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