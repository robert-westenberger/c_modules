#include <stdbool.h>
#ifndef _DOUBLY_LINKED_LIST_H_
#define _DOUBLY_LINKED_LIST_H_

typedef struct DoublyLinkedNode {
    int item; /* data item */
    struct DoublyLinkedNode *next; /* Points to next node */
    struct DoublyLinkedNode *prev; /* Points to next node */
} DoublyLinkedNode;

typedef struct DoublyLinkedList {
    struct DoublyLinkedNode *head;
    struct DoublyLinkedNode *tail;
} DoublyLinkedList;

extern DoublyLinkedList* create_DoublyLinkedList();
extern void insertAtBeginning_DoublyLinkedList(DoublyLinkedList** list, int value);
extern void insertAtEnd_DoublyLinkedList(DoublyLinkedList** list, int value);
extern void insertBefore_DoublyLinkedList(DoublyLinkedList** list, DoublyLinkedNode** node, int value);
extern void insertAfter_DoublyLinkedList(DoublyLinkedList** list, DoublyLinkedNode** node, int value);
extern void remove_DoublyLinkedList(DoublyLinkedList** list, DoublyLinkedNode** node);
extern void traverseForward_DoublyLinkedList(DoublyLinkedList** list, void (*callback)(int item));
#endif