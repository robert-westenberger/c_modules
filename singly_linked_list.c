#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include "singly_linked_list.h"

SinglyLinkedList *create_SinglyLinkedList(NodeDataOps data_ops)
{
    SinglyLinkedList *list;
    list = malloc(sizeof(*list));
    if (NULL == list)
    {
        fprintf(stderr, "malloc() failed in file %s at line # %d", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->data_ops = data_ops;
    
    return list;
}

void insert_SinglyLinkedList(SinglyLinkedList *list, const void *data) {
    Node* node;
    node = malloc(sizeof(Node*));
    node->data = list->data_ops.cp(data);
    node->next = list->head;
    list->head = node;
    list->size++;
}

int sizeof_SinglyLinkedList(SinglyLinkedList *list) {
    return list->size;
}

void deleteValue_SinglyLinkedList(SinglyLinkedList *list, const void *data)
{
    Node *temp = list->head, *prev;

    /* head contains item to be deleted */
    if (temp != NULL && list->data_ops.eq(temp->data, data))
    {
        list->head = temp->next;
        list->size--;
        free(temp);
        return;
    }

    /* Search the list for the value to be deleted, 
    keeping track of the previous node as it needs to be 
    updated. */
    while (temp != NULL && !list->data_ops.eq(temp->data, data))
    {
        prev = temp;
        temp = temp->next;
    }

    /* Value was not in linked list */
    if (temp == NULL)
    {
        return;
    }
    list->size--;
    prev->next = temp->next;
    free(temp); // Free memory
}
bool contains_SinglyLinkedList(SinglyLinkedList *list, const void *data) {
  Node *ptr = list->head;
  while (ptr) {
      if (list->data_ops.eq(ptr->data, data)) {
          return true;
      }
      ptr = ptr->next;
  }
  return false;
}
void free_SinglyLinkedList(SinglyLinkedList *list)
{
    // WIP
}

void print_SinglyLinkedList(SinglyLinkedList *list, void (*print_data)(const void *data)) {
    Node *ptr = list->head;
    while (ptr) {
        print_data(ptr->data);
        ptr = ptr->next;
    }
}
    /* String operations*/

    void *string_cp(const void *data)
{
    const char *input = (const char *)data;
    size_t input_length = strlen(input) + 1;
    char *result;
    result = malloc(sizeof(*result) * input_length);
    if (NULL == result)
    {
        fprintf(stderr, "malloc() failed in file %s at line # %d", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    strcpy(result, input);
    return result;
}
bool string_eq(const void *data1, const void *data2)
{
    const char *str1 = (const char *)data1;
    const char *str2 = (const char *)data2;
    return !(strcmp(str1, str2)) ? true : false;
}
void string_free(void *data)
{
    free(data);
}
void string_print(const void *data)
{
    printf("%s\n", (const char *)data);
}

NodeDataOps data_ops_string = {string_cp, string_free, string_eq};