#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "doubly_linked_list.h"

DoublyLinkedList* create_DoublyLinkedList() {
    DoublyLinkedList *p = malloc(sizeof(DoublyLinkedList));
    p->head = NULL;
    p->tail = NULL;
    return p;
}
static bool isEmpty_DoublyLinkedList(DoublyLinkedList* list) {
    return list->head == NULL;
}
void insertAtBeginning_DoublyLinkedList(DoublyLinkedList** list, int value){
    DoublyLinkedNode *newNode;
    newNode = malloc(sizeof(DoublyLinkedNode));
    newNode->item = value;
    newNode->next = (*list)->head;
    newNode->prev = NULL;

    if (isEmpty_DoublyLinkedList(*list)) {
        (*list)->tail = newNode;
    }
    (*list)->head = newNode; 
}
void insertAtEnd_DoublyLinkedList(DoublyLinkedList** list, int value) {
    DoublyLinkedNode *newNode;
    newNode = malloc(sizeof(DoublyLinkedNode));
    newNode->item = value;
    newNode->next = NULL;
    newNode->prev = (*list)->tail;

    if (isEmpty_DoublyLinkedList(*list)) {
        (*list)->head = newNode;
    }
    (*list)->tail = newNode;
}
void insertBefore_DoublyLinkedList(DoublyLinkedList** list, DoublyLinkedNode** node, int value) {
    DoublyLinkedNode *newNode;
    newNode = malloc(sizeof(DoublyLinkedNode));
    newNode->item = value;

    newNode->next = *node;
    newNode->prev = (*node)->prev;
    (*node)->prev = newNode;
    if (newNode->prev != NULL) {
        newNode->prev->next = newNode;
    } else {
        (*list)->head = newNode;
    }
}
void insertAfter_DoublyLinkedList(DoublyLinkedList** list, DoublyLinkedNode** node, int value) {
    DoublyLinkedNode *newNode;
    newNode = malloc(sizeof(DoublyLinkedNode));
    newNode->item = value;

    newNode->next = (*node)->next;
    newNode->prev = *node;
    (*node)->next = newNode;
    if (newNode->next != NULL) {
        newNode->prev->next = newNode;
    } else {
        (*list)->tail = newNode;
    } 

}

void remove_DoublyLinkedList(DoublyLinkedList** list, DoublyLinkedNode** node) {
    // We are deleting head..
    if ((*node) == (*list)->head) { 
        (*list)->head = (*node)->next;
  
    }
    // We are deleting tail..
    if ((*node) == (*list)->tail) { 
        (*list)->tail = (*node)->prev;
        
    }
    if ((*node)->next != NULL) {
        (*node)->next->prev = (*node)->prev;
    } 
    if ((*node)->prev != NULL) {
        (*node)->prev->next = (*node)->next;
    }
    free(node);
    return;
}

static void traverseForward_DoublyLinkedListIter(DoublyLinkedNode** node, void (*callback)(int item)) {
    callback((*node)->item);
    if ((*node)->next != NULL ){ 
        return traverseForward_DoublyLinkedListIter(&(*node)->next, callback);
    }
}
void traverseForward_DoublyLinkedList(DoublyLinkedList** list, void (*callback)(int item)) {
    if ((*list)->head != NULL ){
        return traverseForward_DoublyLinkedListIter(&(*list)->head, callback);
    }
}