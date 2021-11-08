#include <stdbool.h>
#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct Queue {
  int front, rear, size;
  unsigned capacity;
  int* array;
} Queue;


extern Queue* create_Queue(unsigned capacity);
extern bool isFull_Queue(Queue* queue);
extern bool isEmpty_Queue(Queue* queue);
extern void enqueue_Queue(Queue* queue, int item);
extern int dequeue_Queue(Queue* queue);
extern int front_Queue(Queue *queue);
extern int rear_Queue(Queue *queue);
#endif