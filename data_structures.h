#ifndef _DATA_STRUCTURES_H_
#define _DATA_STRUCTURES_H_

typedef struct {  
    int top;
    int maxsize;
    int* items;
} Stack;


extern Stack* createStack(int maxsize);
extern int isFull(Stack* stack);
extern int isEmpty(Stack* stack);
extern void push(Stack* stack, int item);
extern int pop(Stack* stack);
#endif