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

/* Increases capacity of the dynamic array, returning false if there is an
error. Just for simplicity the capacity is doubled each time. */
extern bool enlarge_DynamicArray(DynamicArray* array);

/* Inserts item into array at index, shifting others to the right if necessary.
Returns false is there is an error. */
extern bool addAtIndex_DynamicArray(DynamicArray* array, int item, int index);

/* Inserts item into array at the beginning, shifting everything else 
1 index to the right. Returns false if error. */
extern bool prepend_DynamicArray(DynamicArray* array, int item);

/* Inserts item into array at the end. Returns false if error. */
extern bool append_DynamicArray(DynamicArray* array, int item);

/* Gets and returns item at position index. Doesnt check if its a valid
index or anything, so behavior will be undefined if given a bad index. */
extern int getItemAtIndex_DynamicArray(DynamicArray* array, int item);
/* Removes item from array at index, shifting others to the right if necessary,
and returns the item. 
*/
extern int removeAtIndex_DynamicArray(DynamicArray* array, int index);

/* Replaces item at given index
*/
extern int replaceAtIndex_DynamicArray(DynamicArray* array, int item, int index);
/* Returns size of the dynamic array */
extern int size_DynamicArray(DynamicArray* array);

/* Executes callback for each element in the array. */
extern void forEach_DynamicArray(DynamicArray* array, int (*callback)(void));


/* SinglyLinkedList Node */
typedef struct Node {
    int item; /* data item */
    struct Node *next; /* Points to next node */
} Node;

typedef struct List {
    struct Node *head; /* Points to first item (the head of the list) */
} List;

extern List* createList();
extern void pushToList(List** list, int value);
extern void printList(List* list);
extern void deleteFromListByValue(List** list, int value);
extern void deleteFromListByValue2(List** list, int value);

#endif