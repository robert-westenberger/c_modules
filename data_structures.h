#ifndef _DATA_STRUCTURES_H_
#define _DATA_STRUCTURES_H_

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