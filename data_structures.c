#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"


Stack* createStack(int maxsize) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->maxsize = maxsize;
    stack->top = -1;
    stack->items = (int*)malloc(stack->maxsize * sizeof(int));
    return stack; 
}

int isFull(Stack* stack)
{
    return stack->top == stack->maxsize - 1;
}

int isEmpty(Stack* stack)
{
    return stack->top == -1;
}

void push(Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->items[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}

int pop(Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->items[stack->top--];
}