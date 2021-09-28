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


extern DynamicArray *create_DynamicArray();
extern bool enlarge_DynamicArray(DynamicArray* array);
extern bool shrink_DynamicArray(DynamicArray* array);
extern bool addAtIndex_DynamicArray(DynamicArray* array, int item, int index);
extern bool prepend_DynamicArray(DynamicArray* array, int item);
extern bool append_DynamicArray(DynamicArray* array, int item);
extern int getItemAtIndex_DynamicArray(DynamicArray* array, int item);
extern int removeAtIndex_DynamicArray(DynamicArray* array, int index);
extern int removeAtIndex2_DynamicArray(DynamicArray* array, int index);
extern int replaceAtIndex_DynamicArray(DynamicArray* array, int item, int index);
extern int size_DynamicArray(DynamicArray* array);
extern void forEach_DynamicArray(DynamicArray* array, void (*callback)(int item));


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


/* Binary Search Tree */
#endif