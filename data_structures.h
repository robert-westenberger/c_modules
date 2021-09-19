#include <stdbool.h>
#ifndef _DATA_STRUCTURES_H_
#define _DATA_STRUCTURES_H_
/* Todo: Make everything dynamic? Right now everything is just ints. */
/* Stack */
typedef struct Stack {  
    int top;
    int maxsize;
    int* items;
} Stack;


extern Stack* createStack(int maxsize);
extern int isFullStack(Stack* stack);
extern int isEmptyStack(Stack* stack);
extern void push(Stack* stack, int item);
extern int pop(Stack* stack);

/* Dynamic Array */
typedef struct DynamicArray {
    int capacity; /* Total capacity of the internal fixed size array */
    int size; /* Current number of items in the array */
    int *items;
} DynamicArray;

/* creates and returns a pointer to a new dynamic array
of size 0. If there is no more memory, returns NULL. */
extern DynamicArray *create_DynamicArray();

/* Inserts item into array at index, shifting others to the right if necessary.
Returns false is there is an error. */
extern bool addAtIndex_DynamicArray(DynamicArray* array, int item, int index);

/* Inserts item into array at the beginning, shifting everything else 
1 index to the right. Returns false if error. */
extern bool prepend_DynamicArray(DynamicArray* array, int item);

/* Inserts item into array at the end. Returns false if error. */
extern bool append_DynamicArray(DynamicArray* array, int item);

/* Removes item from array at index, shifting others to the right if necessary,
and returns the item. 
*/
extern int removeAtIndex_DynamicArray(DynamicArray* array, int item, int index);

/* Returns size of the dynamic array */
extern int size_DynamicArray(DynamicArray* array);

/* Executes callback for each element in the array. */
extern void forEach_DynamicArray(DynamicArray* array, int (*callback)(void));


/* SinglyLinkedList Node */
typedef struct Node {
    int item; /* data item */
    struct Node *next;
} Node;

typedef struct List {
    struct Node *head;
} List;

extern List *createList();
extern void pushToList(List** list, int value);
extern void printList(List* list);
extern void deleteFromListByValue(List** list, int value);
extern void deleteFromListByValue2(List** list, int value);
// extern Node* searchList(Node* list, int value);
#endif