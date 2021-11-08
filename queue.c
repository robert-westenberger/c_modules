#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* create_Queue(unsigned capacity) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->capacity = capacity;
	queue->front = queue->size = 0;
	queue->rear = capacity - 1;
	queue->array = (int *)malloc(queue->capacity * sizeof(int));
	return queue;
}
bool isFull_Queue(Queue *queue) {
	return (queue->size == queue->capacity);
}
bool isEmpty_Queue(Queue *queue) {
	return (queue->size == 0);
}
void enqueue_Queue(Queue *queue, int item) {
	if (isFull_Queue(queue))
		return;
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1;
	printf("%d enqueued to queue\n", item);
}
int dequeue_Queue(Queue *queue) {
	if (isEmpty_Queue(queue))
		return INT_MIN;
	int item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;
	return item;
}
int front_Queue(Queue *queue) {
	if (isEmpty_Queue(queue))
		return INT_MIN;
	return queue->array[queue->front];
}
int rear_Queue(Queue *queue) {
	if (isEmpty_Queue(queue))
		return INT_MIN;
	return queue->array[queue->rear];
}